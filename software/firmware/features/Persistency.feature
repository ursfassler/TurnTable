# language: en
Feature: Persistency
	Scenario: Persisting a value
		Given the communication to the device over RS232
		When a parameter value is sent to the device
		Then this parameter is persisted on the device


	Scenario Outline: Persisted Parameters
		Given I want to persist parameter <parameter>
		Then I have to send the command 'send <parameter_name> <value_example>'
		And end the command with a newline character

		Examples:
		| parameter            | parameter_name       | value_example   |
		| Wi-Fi SSID           | wifi_ssid            | this_is_an_ssid |
		| Wi-Fi Password       | wifi_password        | wifi_password   |
		| Host IP              | host_ip              | 123.456.78.9    |
		| MQTT Broker Username | mqtt_broker_username | username_123    |
		| MQTT Broker Password | mqtt_broker_password | mqtt_password   |


	Scenario: Reading persisted values
		Given the communication to the device over RS232
		When a parameter read command is sent
		And the command is in the form 'read <parameter_name>'
		Then the persisted parameter value is returned
		And the returned message has the form '<parameter_name> <parameter_value>'
		And the message ends with a newline character
