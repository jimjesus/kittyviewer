#!/usr/bin/python
"""\
@file   run_build_test.py
@author Nat Goodspeed
@date   2009-09-03
@brief  Helper script to allow CMake to run some command after setting
        environment variables.

CMake has commands to run an external program. But remember that each CMake
command must be backed by multiple build-system implementations. Unfortunately
it seems CMake can't promise that every target build system can set specified
environment variables before running the external program of interest.

This helper script is a workaround. It simply sets the requested environment
variables and then executes the program specified on the rest of its command
line.

Example:

python run_build_test.py -DFOO=bar myprog somearg otherarg

sets environment variable FOO=bar, then runs:
myprog somearg otherarg

$LicenseInfo:firstyear=2009&license=mit$

Copyright (c) 2009-2010, Linden Research, Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
$/LicenseInfo$

"""

import os
import sys
import subprocess

def main(command, libpath=[], vars={}):
    """Pass:
    command is a sequence (e.g. a list) of strings. The first item in the list
    must be the command name, the rest are its arguments.

    libpath is a sequence of directory pathnames. These will be appended to
    the platform-specific dynamic library search path environment variable.

    vars is a dict of arbitrary (var, value) pairs to be added to the
    environment before running 'command'.

    This function runs the specified command, waits for it to terminate and
    returns its return code. This will be negative if the command terminated
    with a signal, else it will be the process's specified exit code.
    """
    # Handle platform-dependent libpath first.
    if sys.platform == "win32":
        lpvars = ["PATH"]
    elif sys.platform == "darwin":
        lpvars = ["LD_LIBRARY_PATH", "DYLD_LIBRARY_PATH"]
    elif sys.platform.startswith("linux"):
        lpvars = ["LD_LIBRARY_PATH"]
    else:
        # No idea what the right pathname might be! But only crump if this
        # feature is requested.
        if libpath:
            raise NotImplemented("run_build_test: unknown platform %s" % sys.platform)
        lpvars = []
    for var in lpvars:
        # Split the existing path. Bear in mind that the variable in question
        # might not exist; instead of KeyError, just use an empty string.
        dirs = os.environ.get(var, "").split(os.pathsep)
        # Append the sequence in libpath
        print "%s += %r" % (var, libpath)
        dirs.extend(libpath)
        # Now rebuild the path string. This way we use a minimum of separators
        # -- and we avoid adding a pointless separator when libpath is empty.
        os.environ[var] = os.pathsep.join(dirs)
    # Now handle arbitrary environment variables. The tricky part is ensuring
    # that all the keys and values we try to pass are actually strings.
    if vars:
         print "Setting:"
         for key, value in vars.iteritems():
             print "%s=%s" % (key, value)
    os.environ.update(dict([(str(key), str(value)) for key, value in vars.iteritems()]))
    # Run the child process.
    print "Running: %s" % " ".join(command)
    return subprocess.call(command)

if __name__ == "__main__":
    from optparse import OptionParser
    parser = OptionParser(usage="usage: %prog [options] command args...")
    # We want optparse support for the options we ourselves handle -- but we
    # DO NOT want it looking at options for the executable we intend to run,
    # rejecting them as invalid because we don't define them. So configure the
    # parser to stop looking for options as soon as it sees the first
    # positional argument (traditional Unix syntax).
    parser.disable_interspersed_args()
    parser.add_option("-D", "--define", dest="vars", default=[], action="append",
                      metavar="VAR=value",
                      help="Add VAR=value to the env variables defined")
    parser.add_option("-l", "--libpath", dest="libpath", default=[], action="append",
                      metavar="DIR",
                      help="Add DIR to the platform-dependent DLL search path")
    opts, args = parser.parse_args()
    # What we have in opts.vars is a list of strings of the form "VAR=value"
    # or possibly just "VAR". What we want is a dict. We can build that dict by
    # constructing a list of ["VAR", "value"] pairs -- so split each
    # "VAR=value" string on the '=' sign (but only once, in case we have
    # "VAR=some=user=string"). To handle the case of just "VAR", append "" to
    # the list returned by split(), then slice off anything after the pair we
    # want.
    rc = main(command=args, libpath=opts.libpath,
              vars=dict([(pair.split('=', 1) + [""])[:2] for pair in opts.vars]))
    if rc not in (None, 0):
        print >>sys.stderr, "Failure running: %s" % " ".join(args)
        print >>sys.stderr, "Error: %s" % rc
    sys.exit((rc < 0) and 255 or rc)
