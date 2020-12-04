package com.controller;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import com.model.MemberDAO;
import com.model.MemberDTO;
import com.model.WaterDAO;
import com.model.WaterDTO;

@WebServlet("/check.do")
public class MemberCheckController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		PrintWriter out = response.getWriter();
		String id = request.getParameter("id");

		System.out.println(id);

		MemberDAO dao = new MemberDAO();
		int cnt = dao.Idcheck(id);
		System.out.println(cnt);

		if (cnt > 0) {
			out.print("1");
		} else {
			out.print("0");
		}

	}

}
