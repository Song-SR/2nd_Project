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
import com.model.SettingDTO;
import com.model.WaterDAO;
import com.model.WaterDTO;

@WebServlet("/wifi")
public class ArduinoFunctionWifi extends HttpServlet {

	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		PrintWriter out = response.getWriter();
		WaterDAO wdao = new WaterDAO();
		WaterDTO wdto = new WaterDTO();
		SettingDAO sdao = new SettingDAO();
		SettingDTO sdto = new SettingDTO();
		
		// input값 ---
		String serialCode = request.getParameter("sc");
		int waterLevel = Integer.parseInt(request.getParameter("wl"));
		String waterTemp = request.getParameter("tp");
		String feedPressure = request.getParameter("fp");  //  초음파센서로 변경
		// ----------
		
		System.out.println("수위 input : " + waterLevel);
		
		Calendar cal = Calendar.getInstance();
		int hour = cal.get(Calendar.HOUR_OF_DAY);
		int min = cal.get(Calendar.MINUTE);
		int sec = cal.get(Calendar.SECOND);

		System.out.println(hour + "시 " + min + "분 " + sec + "초");
		
		// 수위 cm로 전환 ---
		int watercm = 12;
		System.out.println(watercm);
		if(waterLevel > 520) {
			watercm += 3;
		}else if(waterLevel > 430) {
			watercm += 2;
		}else if(waterLevel > 300) {
			watercm += 1;
		}
		String waterstrcm = Integer.toString(watercm);
		// ----------
		
		// db저장 ---
		wdto.setWatertemp(waterTemp);
		wdto.setWaterlevel(waterstrcm);
		wdto.setFeedpressure(feedPressure);
		wdao.updateWater(wdto, serialCode);
		
		// ----------

		// 코드 체크용 ---
		System.out.println("수온 : " + waterTemp + "도");
		System.out.println("수위 : " + watercm + "cm");
		System.out.println("먹이량 : " + feedPressure);  // 높을수록 적게 남은것
		// ----------
		// output값 ---  (아두이노로 보낼 값들)
		String sv = "0";  // 서버모터
		String heat = "0";  // 발열패드
		String ledInfo = "00";  // 00 : off, 01~13 : 컬러
		// ----------
		
		sdto = sdao.getSettingInfo(serialCode);
		
		// led기능
		if(sdto.getSet_power().equals("off")) {
			ledInfo = "00";
		}else {
			ledInfo = sdto.getSet_color();
		}
		
		// 먹이공급
		int t_t = Integer.parseInt(sdto.getSet_feed());  // web에서 설정한 공급시간간격
		
		String feeding = wdao.getWaterInfo(serialCode).getFeeding();
		
		for(int i = 0; i < 20; i++) {  // 현재 분당 기준
			if(((t_t*i == min) && (wdao.updateFeed(t_t/2, serialCode) > 0)) || feeding.equals("ON")) {
				wdao.feedUpdateNow(serialCode);
				wdao.updateFeeding(serialCode, "OFF");
				sv = "1";
				break;
			}else {
				sv = "0";
			}
		}
		System.out.println((sv.equals("1"))? "먹이주기on" : "먹이주기off");
		
		// 발열패드
		int set_Temp = Integer.parseInt(sdto.getSet_temp());
		float wTemp = Float.parseFloat(waterTemp);
		System.out.println("온도차이 : " + (float)(set_Temp-wTemp));
		if(set_Temp > wTemp) {
			heat = "1"; // 2. 발열패드
			System.out.println("발열패드 on");
		}else {
			heat = "0";
			System.out.println("발열패드 off");
		}
		
		// /먹이공급(1),led전원(1),led색(2)/
		out.print("/" + sv + heat + ledInfo + "/");
	}

}
