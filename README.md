# guessccsid

package that does it's best to guess the ccsid of a stream or file

## Build

To build the code:
-`cd repo-root`
-`./build`

If you need to set up configuration specific to your server, create a file called `SERVER.cfg`
where `SERVER` is the name returned from `hostname -s` (see `setenv` to see how it is source'd).
