package com.controller;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.model.SettingDAO;
import com.model.SettingDTO;
import com.model.WaterDAO;
import com.model.WaterDTO;

@WebServlet("/update")
public class SettingUpdateController extends HttpServlet {
	private static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	
	request.setCharacterEncoding("utf-8");
	String ctx = request.getContextPath();
	
	HttpSession session = request.getSession();
	String serialCode = (String)session.getAttribute("serialCode");
	System.out.println("시리얼 :" +  serialCode);
	
	String set_temp = request.getParameter("temp");
	String set_level = request.getParameter("level");
	String set_power = request.getParameter("toggle-slider");
	String set_feed = request.getParameter("feed");
	String set_color = request.getParameter("colbtn");
	System.out.println("set_feed"+set_feed);
	System.out.println("set_color"+set_color);

	if(set_power == null) {
		set_power = "off";
		set_color = "0";
	}
	
	SettingDTO sdto = new SettingDTO();
	sdto.setSet_temp(set_temp);
	sdto.setSet_level(set_level);
	sdto.setSet_power(set_power);
	sdto.setSet_feed(set_feed);
	
//	if(set_color == null) {  // 이거 아직 컬러버튼들 작동방식몰라서 null값이라 우선 0으로 대체
//		set_color = "0";
//	}
//	
	sdto.setSet_color(set_color);  // 기존 led_r, led_g, led_b 를 color로 통합하였음 (db table 재생성필요)
	

	
	SettingDAO sdao = new SettingDAO();
	int cnt = sdao.updateSetting(sdto, serialCode);
	System.out.println(cnt);
	
	if(cnt>0) {
		
		
		SettingDTO data = sdao.getSettingInfo(serialCode);
		if(data != null) {
			session.setAttribute("serialCode", serialCode);
			String setPower = sdto.getSet_power();
			String setFeed = sdto.getSet_feed();
			String setTemp = sdto.getSet_temp();
			String setLevel =sdto.getSet_level();
			System.out.println("setPwser : " +setPower);
			session.setAttribute("setPower", sdto.getSet_power());
			session.setAttribute("setColor", sdto.getSet_color());
			session.setAttribute("setFeed", sdto.getSet_feed());
			session.setAttribute("setTemp", sdto.getSet_temp());
			session.setAttribute("setLevel", sdto.getSet_level());
			response.sendRedirect(ctx + "/html5up-astral/index.jsp");
		}
	
		
		
	}else {
		  throw new ServletException("error"); 
	}
	
	}

}
