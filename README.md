# ofxModernSocket

openframeworks socket library with c++11 thread and boost.asio

this is experimental addon, not stable, W.I.P.

## API

### ofxModernUDPReceiver

* bool setup(port)
* void receive(const boost::system::error_code &error_code,
               array<char, buf_size> &buf,
               size_t len)

### ofxModernOscReceiver

* bool setup(port)
* addCallback(const string &address, function<void(ofxModernOscMessage &)>)

#### ofxModernOscMessage
#### ofxModernOscArgument

## Included Libraries

### boost.asio 1.58 (same ver. as boost in oF 0.9.3)

* [boost.org](http://www.boost.org) &copy; 2003-
* [License](https://github.com/2bbb/ofxModernSocket/blob/master/libs/boost/LICENSE_1_0.txt)
* [sourceforge](https://sourceforge.net/projects/boost/files/boost/1.58.0/)

### original oscpp

* [Stefan Kersten](https://github.com/kaoskorobase) &copy; 2004-
* [License](https://github.com/2bbb/ofxModernSocket/blob/master/libs/oscpp/LICENSE)
* [github](https://github.com/kaoskorobase/oscpp/tree/b556a5e63fbd38da5b0e1934fe525bf9ca0a7fb1)

## Update history

### 2016/03/20 ver 0.0.0 release

## License (ofxModernSocket)

MIT License.

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com

## At the last

Please create a new issue if there is a problem. And please throw a pull request if you have a cool idea!!
