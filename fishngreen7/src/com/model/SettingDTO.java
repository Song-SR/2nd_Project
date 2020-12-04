package com.model;

public class SettingDTO {
	
	private String serialcode;
	private String set_temp;
	private String set_level;
	private String set_power;
	private String set_color;
	private String set_feed;
	
	public SettingDTO() {  }

	public SettingDTO(String serialcode, String set_temp, String set_level, String set_power, String set_color,
			String set_feed) {
		super();
		this.serialcode = serialcode;
		this.set_temp = set_temp;
		this.set_level = set_level;
		this.set_power = set_power;
		this.set_color = set_color;
		this.set_feed = set_feed;
	}

	public String getSerialcode() {
		return serialcode;
	}

	public void setSerialcode(String serialcode) {
		this.serialcode = serialcode;
	}

	public String getSet_temp() {
		return set_temp;
	}

	public void setSet_temp(String set_temp) {
		this.set_temp = set_temp;
	}

	public String getSet_level() {
		return set_level;
	}

	public void setSet_level(String set_level) {
		this.set_level = set_level;
	}

	public String getSet_power() {
		return set_power;
	}

	public void setSet_power(String set_power) {
		this.set_power = set_power;
	}

	public String getSet_color() {
		return set_color;
	}

	public void setSet_color(String set_color) {
		this.set_color = set_color;
	}

	public String getSet_feed() {
		return set_feed;
	}

	public void setSet_feed(String set_feed) {
		this.set_feed = set_feed;
	}

	

	
}
