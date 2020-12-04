package com.model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WaterDAO {
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
   
   WaterDTO wdto = new WaterDTO();
   
   public WaterDTO getWaterInfo(String serialCode) {
      conn = getConn();
      String sql = "select * from water where serialcode = ?";
      try {
         ps=conn.prepareStatement(sql);
         ps.setString(1, serialCode);
         rs = ps.executeQuery();
         
         if(rs.next()) {
            String ledPower = rs.getString("led_power");
            String feedTime = rs.getString("feedtime");
            String waterTemp = rs.getString("watertemp");
            String waterLevel = rs.getString("waterlevel");
            String feedPressure = rs.getString("feedpressure");
            String feeding = rs.getString("feeding");

            wdto.setLed_power(ledPower);
            wdto.setFeedtime(feedTime);
            wdto.setWatertemp(waterTemp);
            wdto.setWaterlevel(waterLevel);
            wdto.setFeedpressure(feedPressure);
            wdto.setFeeding(feeding);
            
         }
      } catch (Exception e) {
         e.printStackTrace();
      } finally {
         close();
      }
      return wdto;
   }
   
   public void insertWater(String serialCode) {
         conn = getConn();
         String sql = "insert into water values(?,'20','12','OFF','0','0','OFF', sysdate)";
         cnt = 0;
         try {
            ps=conn.prepareStatement(sql);
            ps.setString(1, serialCode);
            cnt = ps.executeUpdate();
            
         } catch (Exception e) {
            e.printStackTrace();
         } finally {
            close();
         }
      }
   
	public void updateWater(WaterDTO wdto, String serialCode) {
		conn= getConn();
		String sql = "update water set watertemp = ?, waterlevel = ?, feedpressure = ? where serialcode=?";
		try {
			ps=conn.prepareStatement(sql);
			ps.setString(1, wdto.getWatertemp());
			ps.setString(2, wdto.getWaterlevel());
			ps.setString(3, wdto.getFeedpressure());
			ps.setString(4, serialCode);
			
			cnt = ps.executeUpdate(); 
		} catch (SQLException e) {
			e.printStackTrace();
		}finally{
			close();
			}
		}
	
   public void feedUpdateNow(String serialCode) {
      conn = getConn();
      String sql = "update water set feedtime=sysdate where serialcode=?";
      try {
         ps = conn.prepareStatement(sql);
         ps.setString(1, serialCode);

         cnt = ps.executeUpdate();
      } catch (SQLException e) {
         e.printStackTrace();
      } finally {
         close();
      }
   }
   
   
   public int updateFeed(Integer time, String serialcode) {
      conn = getConn();
      String sql = "select feedtime from water where sysdate-(?/24/60) >= feedtime and serialcode = ?";
      cnt = 0;
      try {
         ps=conn.prepareStatement(sql);
         ps.setInt(1, time);
         ps.setString(2, serialcode);
         rs = ps.executeQuery();
         if(rs.next()) {
            cnt++;
         }
         
      } catch (Exception e) {
         e.printStackTrace();
      } finally {
         close();
      }
      return cnt;  // 0이면 이미 먹이줬음. 1이면 먹이 준지 오래된 것
      
   }
   
   public void updateFeeding(String serialCode, String check) {
	      conn = getConn();
	      String sql = "update water set feeding = ? where serialcode=?";
	      try {
	         ps = conn.prepareStatement(sql);
	         ps.setString(1, check);
	         ps.setString(2, serialCode);
	         cnt = ps.executeUpdate();
	      } catch (SQLException e) {
	         e.printStackTrace();
	      } finally {
	         close();
	      }
	   }
}