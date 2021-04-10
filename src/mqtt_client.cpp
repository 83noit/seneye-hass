#include "mqtt_client.h"

#include "log.h"

MqttClient::MqttClient(const std::string id, const std::string topic,
                       const std::string host, int port,
                       const std::string username, const std::string password)
    : mosquittopp(id.c_str()) {
  mosqpp::lib_init();  // Mandatory initialization for mosquitto library
  this->keepalive = 60;
  this->id = id;
  this->topic = topic;
  this->host = host;
  this->port = port;
  mosquittopp::username_pw_set(username.c_str(), password.c_str());
  connect(this->host.c_str(), this->port, this->keepalive);
}

// TODO: Use constructor delegation.
MqttClient::MqttClient(const std::string id, const std::string topic,
                       const std::string host, int port)
    : mosquittopp(id.c_str()) {
  mosqpp::lib_init();  // Mandatory initialization for mosquitto library
  this->keepalive = 60;
  this->id = id;
  this->topic = topic;
  this->host = host;
  this->port = port;
  connect(this->host.c_str(), this->port, this->keepalive);
}

MqttClient::~MqttClient() {
  mosqpp::lib_cleanup();  // Mosquitto library cleanup
}

void MqttClient::on_connect(int rc) {
  if (!rc) {
    std::clog << kLogInfo << "MQTT connected to server." << std::endl;
  } else {
    std::clog << kLogWarning << "MQTT connection with server failed (" << rc
              << ")." << std::endl;
  }
}

void MqttClient::on_disconnect(int rc) {
  std::clog << kLogWarning << "MQTT disconnection (" << rc << ")." << std::endl;
}

void MqttClient::on_publish(int mid) {
  std::clog << kLogDebug << "MQTT message " << mid << " published."
            << std::endl;
}

bool MqttClient::send_message(const std::string& message) {
    return send_message(message, this->topic.c_str());
}

bool MqttClient::send_message(const std::string& message, const char* topic) {
  // Send message - depending on QoS, mosquitto lib managed re-submission this
  // the thread
  //
  // * NULL : Message Id (int *) this allow to latter get status of each message
  // * topic : topic to be used
  // * lenght of the message
  // * message
  // * qos (0,1,2)
  // * retain (boolean) - indicates if message is retained on broker or not
  // Should return MOSQ_ERR_SUCCESS
  int ret = publish(NULL, topic, message.length(),
                    message.c_str(), 1, false);
  return (ret == MOSQ_ERR_SUCCESS);
}
