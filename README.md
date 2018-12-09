# egg

A bare bones alarm clock/egg timer made in C++.

While learning C++ I needed a small project; ended up with this. It will actually be kind of usefull timing my eggs..

Currently it will only fire the alarm at an absolute time, e.g. 12:15:35. I'm planning to add a relative mode as well, just need to understand the clock/time system a bit better.

## Compiling

You'll need

- A C++17 compatible clang++ compiler
- SDL2 (base and mixer package)
- Boost/Program Options

Clone the repo and run ````$ ./build.sh```` in the base directory.

Currently I've setup the build script assuming that SDL is installed in ````Library/Frameworks````. I might use a propper build system later on..

## Contributing

Contributions are always welcome!

When contributing to this repository, please first discuss the change you wish to make via the issue tracker, email, or any other method with the owner of this repository before making a change.

Please note that we have a code of conduct, you are required to follow it in all your interactions with the project.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/frklan/egg/tags).

## Authors

* **Fredrik Andersson** - *Initial work* - [frklan](https://github.com/frklan)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
