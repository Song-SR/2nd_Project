package com.model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MemberDAO {
	Connection conn = null;
	PreparedStatement ps = null;
	ResultSet rs = null;
	int cnt= 0;

	static {
		try {
			Class.forName("oracle.jdbc.driver.OracleDriver");
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
	
	public Connection getConn() {
		
		String URL = "jdbc:oracle:thin:@localhost:1521:xe";
		String user = "hr";
		String password = "hr";
		
		try {
			conn = DriverManager.getConnection(URL, user, password);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return conn;
	}

	public void close() {

		try {
			if (rs != null) {
				rs.close();
			}
			if (ps != null) {
				ps.close();
			}
			if (conn != null) {
				conn.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	public int sign(MemberDTO dto) {
		conn = getConn();
		
		String sql = "insert into member values(?,?,serial_seq.nextval,?)";
		
		try {
			ps=conn.prepareStatement(sql);
			
			ps.setString(1,dto.getId());
			ps.setString(2,dto.getPw());
			ps.setString(3,dto.getName());
			
			cnt = ps.executeUpdate();
			
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			close();
		}
		return cnt;

	}
	
	String name = null;
	public String login(MemberDTO dto) {
		conn = getConn();
		String sql = "select name from member where id=? and pw=?";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1, dto.getId());
			ps.setString(2, dto.getPw());
			rs = ps.executeQuery();
			
			if(rs.next()) {
				name = rs.getString("name");
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			close();
		}
		return name;
		
	}
	
	public int Idcheck(String id) {
		conn = getConn();
		cnt = 0;
		String sql = "select * from member where id=?";
		
		try {
			ps= conn.prepareStatement(sql);
			
			ps.setString(1, id);
		
			rs = ps.executeQuery();
			
			if(rs.next()) {
				cnt++;
			}
		} catch (Exception e) {
			e.printStackTrace();
		}finally {
			close();
		}
		return cnt;
	}
	
	String serialCode = null;
	public String getCode(MemberDTO dto) {
		conn = getConn();
		String sql = "select serialcode from member where id=? and pw=?";
		
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1, dto.getId());
			ps.setString(2, dto.getPw());
			rs = ps.executeQuery();
			
			if(rs.next()) {
				serialCode = rs.getString("serialcode");
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			close();
		}
		return serialCode;
		
	}
	
}
