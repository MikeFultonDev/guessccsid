# guessccsid

package that does it's best to guess the ccsid of a stream or file

## References

- [ASCII Basic Table](https://www.ascii-code.com/)
- [EBCDIC Basic Table](https://www.lookuptables.com/text/ebcdic)
- [UTF-8 Encoding](https://en.wikipedia.org/wiki/UTF-8)

## Build

To build the code:

- `cd repo-root`
- `./build`

If you need to set up configuration specific to your server, create a file called `SERVER.cfg`
where `SERVER` is the name returned from `hostname -s` (see `setenv` to see how it is source'd).
