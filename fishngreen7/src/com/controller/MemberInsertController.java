package com.controller;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.model.MemberDAO;
import com.model.MemberDTO;
import com.model.SettingDAO;
import com.model.WaterDAO;

@WebServlet("/sign.do")
public class MemberInsertController extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void service(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {

		request.setCharacterEncoding("UTF-8");
		response.setCharacterEncoding("UTF-8");
		SettingDAO sdao = new SettingDAO();
		String name = request.getParameter("name");
		String id = request.getParameter("id");
		String pw = request.getParameter("pw");
		String ctx = request.getContextPath();

		MemberDTO dto = new MemberDTO();
		dto.setName(name);
		dto.setId(id);
		dto.setPw(pw);

		MemberDAO dao = new MemberDAO();
		WaterDAO wdao = new WaterDAO();
		int cnt = dao.sign(dto);

		if (cnt > 0) {
			String serialCode = dao.getCode(dto);
			sdao.insertSetting(serialCode);
			wdao.insertWater(serialCode);
			response.sendRedirect(ctx + "/html5up-astral/index.jsp");
		} else {
			throw new ServletException("error");
		}
	}
}
