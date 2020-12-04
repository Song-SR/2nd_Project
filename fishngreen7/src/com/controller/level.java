package com.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/level")
public class level extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		PrintWriter out = response.getWriter();

		String wlevel = request.getParameter("waterlevel");
		String slevel = request.getParameter("setlevel");
		String wtemp = request.getParameter("watertemp");
		String stemp = request.getParameter("settemp");
		String pressure = request.getParameter("feedpressure");

		int a = Integer.parseInt(wlevel);
		int b = Integer.parseInt(slevel);

		float c = Float.parseFloat(wtemp);
		int d = Integer.parseInt(stemp);
		
		float e = Float.parseFloat(pressure);
		
		int cha1 = (b - a);
		float cha2 = (d - c);

//		if (cha1 >= 2) {
//			if (cha2 > 0) {
//				out.print("0");
//			} else {
//				out.print("1");
//			}
//
//		} else {
//			if (cha2 > 0) {
//				out.print("2");
//			} else {
//				out.print("3");
//			}
//		}
		
		String check = "";
		if(cha1 >= 1) {
			check += "1";  // 물공급필요
		}else {
			check += "0";
		}if(cha2 > 0) {
			check += "1";  // 발열필요
		}else {
			check += "0";
		}if(e > 15) {
			check += "2";  // 먹이통이 열려있음
		}else if(e > 4.2){
			check += "1";  // 먹이보충필요
		}else {
			check += "0";
		}
			out.print(check);
	}

}
