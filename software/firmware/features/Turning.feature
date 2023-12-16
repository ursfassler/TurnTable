# language: en
Feature: Turning
	Scenario: Signal received via MQTT
		When a turn signal is received via mqtt
		Then the table turns accordingly
