package com.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.google.gson.JsonObject;
import com.model.MemberDAO;
import com.model.MemberDTO;
import com.model.WaterDAO;
import com.model.WaterDTO;

@WebServlet("/login.do")
public class MemberLoginController extends HttpServlet {

	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		response.setCharacterEncoding("UTF-8");
		request.setCharacterEncoding("UTF-8");
		String ctx = request.getContextPath();
		
		PrintWriter out = response.getWriter();
		String id = request.getParameter("id");
		String pw = request.getParameter("pw");

		MemberDTO dto = new MemberDTO(id, pw);
		MemberDAO dao = new MemberDAO();
		String name = dao.login(dto);
		System.out.println("name : " + name);
		String serialCode = dao.getCode(dto);
		System.out.println("code : " + serialCode);
		if (name != null) { // id와 패스워드가 일치하면
			WaterDAO wdao = new WaterDAO();
			WaterDTO wdto = wdao.getWaterInfo(serialCode);
			
			HttpSession session = request.getSession();
			session.setAttribute("serialCode", serialCode);
			session.setAttribute("name", name);
			session.setAttribute("ledPower", wdto.getLed_power());
			session.setAttribute("feedTime", wdto.getFeedtime());
			session.setAttribute("waterTemp", wdto.getWatertemp());
			session.setAttribute("waterLevel", wdto.getWaterlevel());
			
			// response.sendRedirect(ctx + "/html5up-astral/index.jsp#work");
		} else {
			out.print("fail");
		}

	}
}