package com.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.model.SettingDAO;
import com.model.WaterDAO;
import com.model.WaterDTO;

@WebServlet("/lcdwifi")
public class ArduinoLcdWifi extends HttpServlet {

	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String sc = request.getParameter("sc");
		String lcd = request.getParameter("lcd");
		WaterDAO wdao = new WaterDAO();
		WaterDTO wdto = new WaterDTO();
		PrintWriter out = response.getWriter();
		
		System.out.println("lcd 통신중..");
		Calendar cal = Calendar.getInstance();
		int hour = cal.get(Calendar.HOUR_OF_DAY);
		int min = cal.get(Calendar.MINUTE);
		int sec = cal.get(Calendar.SECOND);
		System.out.println(hour + "시 " + min + "분 " + sec + "초");
		
		System.out.println(sc);
		System.out.println(lcd);
		System.out.println("lcd ------");
		String waterLevel = "15";
		String waterTemp = "00.00";
		String feedRemain = "0";
		
		String led = "";  // 나중에 waterdb에서 가져오기
		
		if(lcd.equals("10")) {
			
		}else if(lcd.equals("11")){
			led = "01";
		}else if(lcd.equals("12")){
			led = "02";
		}else if(lcd.equals("13")){
			led = "03";
		}else if(lcd.equals("14")){
			led = "04";
		}else if(lcd.equals("15")){
			led = "05";
		}else if(lcd.equals("16")){
			led = "06";
		}else if(lcd.equals("17")){
			led = "07";
		}else if(lcd.equals("18")){
			led = "08";
		}else if(lcd.equals("19")){
			led = "09";
		}else if(lcd.equals("20")){
			led = "10";
		}else if(lcd.equals("21")){
			led = "11";
		}else if(lcd.equals("22")){
			led = "12";
		}else if(lcd.equals("23")){
			led = "13";
		}else if(lcd.equals("24")){
			led = "00";
		}else if(lcd.equals("25")){
			wdao.updateFeeding(sc, "ON");
		}
		
		SettingDAO sdao = new SettingDAO();
		sdao.updateLed(sc, led);
		
		wdto = wdao.getWaterInfo(sc);
		
		waterLevel = wdto.getWaterlevel();
		waterTemp = wdto.getWatertemp();
		float feedP = Float.parseFloat(wdto.getFeedpressure());
		if(feedP > 5) {
			feedRemain = "0";  // 먹이 불충분
		}else {
			feedRemain = "1";  // 먹이 충분
		}
		
		out.print("/" + waterLevel + waterTemp + feedRemain + "/");
	}

}
