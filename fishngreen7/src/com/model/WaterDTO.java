package com.model;

public class WaterDTO {
	private String serialcode;

	private String watertemp;
	private String waterlevel;
	private String led_power;
	private String color;
	private String feedpressure;
	private String feeding;
	private String feedtime;

	public WaterDTO() {
	}

	public WaterDTO(String serialcode, String watertemp, String waterlevel, String led_power, String color,
			String feedpressure, String feeding, String feedtime) {
		super();
		this.serialcode = serialcode;
		this.watertemp = watertemp;
		this.waterlevel = waterlevel;
		this.led_power = led_power;
		this.color = color;
		this.feedpressure = feedpressure;
		this.feeding = feeding;
		this.feedtime = feedtime;
	}

	public String getSerialcode() {
		return serialcode;
	}

	public void setSerialcode(String serialcode) {
		this.serialcode = serialcode;
	}

	public String getWatertemp() {
		return watertemp;
	}

	public void setWatertemp(String watertemp) {
		this.watertemp = watertemp;
	}

	public String getWaterlevel() {
		return waterlevel;
	}

	public void setWaterlevel(String waterlevel) {
		this.waterlevel = waterlevel;
	}

	public String getLed_power() {
		return led_power;
	}

	public void setLed_power(String led_power) {
		this.led_power = led_power;
	}

	public String getColor() {
		return color;
	}

	public void setColor(String color) {
		this.color = color;
	}

	public String getFeedpressure() {
		return feedpressure;
	}

	public void setFeedpressure(String feedpressure) {
		this.feedpressure = feedpressure;
	}

	public String getFeeding() {
		return feeding;
	}

	public void setFeeding(String feeding) {
		this.feeding = feeding;
	}

	public String getFeedtime() {
		return feedtime;
	}

	public void setFeedtime(String feedtime) {
		this.feedtime = feedtime;
	}
	
	

}