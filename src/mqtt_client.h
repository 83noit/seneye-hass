#ifndef SRC_MQTT_CLIENT_H_
#define SRC_MQTT_CLIENT_H_

#include <mosquittopp.h>

#include <string>

class MqttClient : public mosqpp::mosquittopp {
  // https://www.disk91.com/2013/technology/programming/mosquitto-c-sample-code-to-publish-message/
 private:
  int keepalive;
  std::string id;
  std::string topic;
  std::string host;
  int port;

  void on_connect(int rc);
  void on_disconnect(int rc);
  void on_publish(int mid);

 public:
  MqttClient(const std::string id, const std::string topic,
             const std::string host, int port);
  MqttClient(const std::string id, const std::string topic,
             const std::string host, int port, const std::string username,
             const std::string password);
  ~MqttClient();
  bool send_message(const std::string& message);
  bool send_message(const std::string& message, const char* topic);
};

#endif  // SRC_MQTT_CLIENT_H_
