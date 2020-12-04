package com.model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SettingDAO {
	Connection conn = null;
	PreparedStatement ps = null;
	ResultSet rs = null;
	int cnt = 0;

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
	
	public void insertSetting(String serialCode) {
		conn = getConn();
		String sql = "insert into setting values(?, '0', '0', 'off', '-', '6')";
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, serialCode);

			cnt = ps.executeUpdate();
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			close();
		}
	}

	public int updateSetting(SettingDTO sdto, String serialCode) {
		conn = getConn();
		String sql = "update setting set set_temp = ? , set_level = ?, set_power =?, set_color=?, set_feed=? where serialcode=?";
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, sdto.getSet_temp());
			ps.setString(2, sdto.getSet_level());
			ps.setString(3, sdto.getSet_power());
			ps.setString(4, sdto.getSet_color());
			ps.setString(5, sdto.getSet_feed());
			ps.setString(6, serialCode);

			cnt = ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			close();
		}
		return cnt;
	}
	
	SettingDTO sdto = new SettingDTO();
	public SettingDTO getSettingInfo(String serialCode) {
	      conn = getConn();
	      String sql = "select * from setting where serialcode = ?";
	      
	      try {
	         ps=conn.prepareStatement(sql);
	         ps.setString(1, serialCode);
	         rs = ps.executeQuery();
	         
	         if(rs.next()) {
	            String set_temp = rs.getString("set_temp");
	            String set_level = rs.getString("set_level");
	            String set_power = rs.getString("set_power");
	            String set_color = rs.getString("set_color");
	            String set_feed = rs.getString("set_feed");
	            sdto.setSet_temp(set_temp);
	            sdto.setSet_level(set_level);
	            sdto.setSet_power(set_power);
	            sdto.setSet_color(set_color);
	            sdto.setSet_feed(set_feed);
	         }
	      } catch (Exception e) {
	         e.printStackTrace();
	      } finally {
	         close();
	      }
	      return sdto;
	   }
	
	public void updateLed(String serialcode, String led) {
		conn = getConn();
		String sql = "update setting set set_color=? where serialcode=?";
		try {
			ps = conn.prepareStatement(sql);
			ps.setString(1, led);
			ps.setString(2, serialcode);

			cnt = ps.executeUpdate();
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			close();
		}
	}

}
