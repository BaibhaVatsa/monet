/**
 * Stephen Hunter Barbella, Baibhav Vatsa
 * GitHub: hman523, baibhavatsa
 * Email: shbarbella@gmail.com, baibhavvatsa@gmail.com
 * Licence: MIT
 * File: TCP.cpp
 */

#include "TCP.h"
#include "../../include/Interpreter.h"
#include <boost/asio.hpp>
#include <numeric>

TCP::TCP() : functions({"tcp.send", "tcp.receive"}) {}

std::set<std::string> TCP::getFunctions() { return functions; }

std::string TCP::eval(const std::string &expression) {
  std::vector<std::string> words = Interpreter::Instance()->split(expression);
  if (words[0] == "tcp.send") {
    return send(words);
  } else if (words[0] == "tcp.receive") {
    return rec(words);
  }
  throw Exception("Fatal implementation error in TCP library in TCP.cpp");
}

int TCP::evalToInt(const std::string &val) {
  return Interpreter::Instance()->strToInt(val);
}

bool TCP::isNum(const std::string &val) {
  return Interpreter::Instance()->isNumber(val);
}

std::string TCP::send(const std::vector<std::string> &expression) {
  if (expression.size() < 4) {
    throw Exception("Wrong number of parameters for tcp.send");
  }

  if (!isNum(expression[2])) {
    throw Exception("Wrong type in second parameter of tcp.send");
  }

  boost::asio::io_context io_service;
  boost::system::error_code ec;
  boost::asio::ip::address ip_address =
      boost::asio::ip::address::from_string(expression[1], ec);

  if (ec) {
    throw Exception("Invalid IP Address in first parameter of tcp.send");
  }

  int port = evalToInt(expression[2]);

  if (port < 0) {
    throw Exception(
        "Invalid port number received in second parameter of tcp.send");
  }

  boost::asio::ip::tcp::endpoint ep(ip_address, port);

  boost::asio::ip::tcp::socket socket(io_service);
  try {
    socket.connect(ep);
  } catch (boost::system::system_error &e) {
    throw Exception("tcp.send failed to connect socket to endpoint " +
                    expression[1] + ":" + std::to_string(port));
  }
  std::string message = expression[3];
  message = std::accumulate(expression.begin() + 4, expression.end(), message,
                            [](const std::string &m1, const std::string &m2) {
                              return m1 + " " + m2;
                            }) +
            "\n";
  boost::system::error_code error;
  boost::asio::write(socket, boost::asio::buffer(message),
                     boost::asio::transfer_all(), error);

  if (error) {
    throw Exception("tcp.send failed to write to socket");
  }

  return "";
}

std::string TCP::rec(const std::vector<std::string> &expression) {
  if (expression.size() != 2) {
    throw Exception("Wrong number of parameters for tcp.receive");
  }

  if (!isNum(expression[1])) {
    throw Exception("Wrong type in first parameter of tcp.receive");
  }

  boost::asio::io_context io_service;
  int port = evalToInt(expression[1]);
  if (port < 0) {
    throw Exception(
        "Invalid port number received in first parameter of tcp.send");
  }
  boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
  boost::asio::streambuf buf;
  try {
    boost::asio::ip::tcp::acceptor acceptor(io_service, ep);
    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);
    boost::system::error_code error;
    boost::asio::read_until(socket, buf, '\n', error);

    if (error) {
      throw Exception("tcp.receive failed to read");
    }
  } catch (boost::system::system_error &e) {
    throw Exception("tcp.receive failed to accept connection on port " +
                    std::to_string(port));
  }

  return boost::asio::buffer_cast<const char *>(buf.data());
}
