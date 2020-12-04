<%@page import="com.model.WaterDAO"%>
<%@page import="com.model.WaterDTO"%>
<%@page import="com.model.SettingDAO"%>
<%@page import="com.model.SettingDTO"%>
<%@ page language="java" contentType="text/html; charset=EUC-KR"
	pageEncoding="UTF-8"%>
<!DOCTYPE HTML>
<html>
<head>
<title>29동성</title>
<meta charset="utf-8" />
<meta name="viewport"
	content="width=device-width, initial-scale=1, user-scalable=no" />
<link rel="stylesheet" href="assets/css/main.css" />
<noscript>
	<link rel="stylesheet" href="assets/css/noscript.css" />
</noscript>
<style>
@import url('https://fonts.googleapis.com/css2?family=Jua&display=swap');
</style>
</head>
<body class="is-preload">



	<%
	String ctx = request.getContextPath();
	String serialCode = (String) session.getAttribute("serialCode");
	String name = (String) session.getAttribute("name");
	if (name == null) {
		name = "ooo";
	}
	String ledPower = (String) session.getAttribute("ledPower");
	String feedTime = (String) session.getAttribute("feedTime");
	String waterTemp = (String) session.getAttribute("waterTemp");
	String waterLevel = (String) session.getAttribute("waterLevel");

	System.out.println("ledpower : " + ledPower);
	System.out.println("feedTime : " + feedTime);
	System.out.println("waterTemp : " + waterTemp);
	System.out.println("waterLevel : " + waterLevel);
	
// 	String set_power = (String) session.getAttribute("setPower");
// 	String set_temp = (String) session.getAttribute("setTemp");
// 	String set_feed = (String) session.getAttribute("setFeed");
// 	String set_level = (String) session.getAttribute("setLevel");
	
// 	System.out.println("set_poser : " +set_power);
// 	System.out.println("set_temp : " +set_temp);
// 	System.out.println("set_feed : " +set_feed);
// 	System.out.println("set_level : " +set_level);

SettingDTO sdto = new SettingDTO();

SettingDAO sdao = new SettingDAO();
sdto = sdao.getSettingInfo(serialCode);

WaterDTO wdto = new WaterDTO();
WaterDAO wdao = new WaterDAO();
wdto = wdao.getWaterInfo(serialCode);


	%>


	<!-- Wrapper-->
	<div id="wrapper">

		<nav id="nav">

			<a href="#" class="fas fa-home"><span>Home</span></a> <a
				href="#contact" class="fas fa-user" id="alogin"><span>Login</span></a>
			<a href="#work" class="fas fa-fish" id="afish"><span>MyFish</span></a> <a
				href="#edit" class="fas fa-cog" id="aedit"><span>Edit</span></a>

		</nav>

		<!-- Main -->
		<div id="main">

			<!-- Me -->
			<article id="home" class="panel intro">

					<img src = "images/yy.PNG" width = "900" height = "410">  


<!-- 			<img src="images/me.png" alt=""  width = "330" height = "330"/>   -->
	
							
				
			</article>

			<!-- Work -->
			<article id="work" class="panel">
				<header>

					<h2 align="center" id="user_name"><%=name%>님의 어항 정보
					</h2>
					<!-- 이름도 db랑 통신해서 값 가져오기~ -->
				</header>

				<section>
					<div align="center">
						<form action="#edit">
							<table class="DBtable">
							<tr>
							<td><br></td>
							<td align ="center">현재상태</td>
							<td align ="center">어항설정</td>
							</tr>
								
								<tr>
									<td align="center">LED</td>
<%-- 									<td align="right" id="ledPowerInfo"><%=ledPower%></td> --%>
									<td  colspan = "2" align ="center" id= "set_color">&nbsp;&nbsp;&nbsp;&nbsp;<%=sdto.getSet_power() %></td>
									<!-- 두번째 열 모두 db에서 값 받아 올 것 -->
								</tr>
								
								<tr>
									<td align="center">FEED</td>
									<td align="center" id="feedTimeInfo"><%=wdto.getFeedtime() %></td>
									<td align ="center" id= "set_feed"><%=sdto.getSet_feed()%>시간</td>
								</tr>
								<tr>
									<td align="center">TEMP</td>
									<td align="center" id="waterTempInfo"><%=wdto.getWatertemp()%><sup>o</sup>C</td>
									<td align ="center" id= "set_temp"><%=sdto.getSet_temp() %><sup>o</sup>C</td>
								</tr>
								<tr>
									<td align="center">LEVEL</td>
									<td align="center" id="waterLevelInfo"><%=wdto.getWaterlevel()%>cm</td>
									<td align ="center" id= "set_level"><%=sdto.getSet_level()%>cm</td>
									
								</tr>
<!-- 								<tr> -->
<!-- 									<td colspan="2"><br></td> -->
<!-- 								</tr> -->
								<tr>
								<td colspan = "3"><div align="center" id="ck1"></div></td>
								</tr>
								<tr>
								<td colspan = "3"><div align="center" id="ck2"></div></td>
								</tr>
								<tr>
								<td colspan = "3"><div align="center" id="ck3"></div></td>
								</tr>
								
								<tr>
								<td colspan ="3" align = "center"><input type = "button" id="check" value = "알림확인">    <input type="submit"
										value="수정하기" id="waterset"></td>
									
								</tr>

							</table>
						</form>
					</div>
				</section>
			</article>

			<!-- Login -->
			<article id="contact" class="panel">
				<header>
					<h2>LOGIN</h2>
				</header>
				<form action="<%=ctx%>/login.do">
					<div>
						<div class="row">
							<div class="col-12">
								<input type="text" name="id" placeholder="ID" id="id" />
							</div>
							<div class="col-12">
								<input type="password" name="pw" placeholder="PASSWORD" id="pw" />
							</div>
							<div class="col-6 col-12-medium" align="left">
								<a href="./sign.jsp">SIGN</a>
							</div>
							<div class="col-6 col-12-medium" align="right">
								<!-- 						<button  id="login">LOGIN</button> -->
								<input type="button" value="LOGIN" id="login">

							</div>
							<div class="loginck" align="right" id="loginck"></div>

						</div>
					</div>
				</form>
			</article>

			<!-- Edit -->
			<article id="edit" class="panel">
				<header>
					<h2 align="center">어항 Control</h2>
				</header>

				<section>
					<div align="center">
						<form action="<%=ctx%>/update">
							<table id="editT" border="1">
								<tr>
									<td align="center">LED</td>
									<td colspan="2">
										<div class="toggleDiv">
											<input type="checkbox" name="toggle-slider"
												id="toggle-slider"> <label for="toggle-slider"
												id="toggle"></label>
										</div>

									</td>
								</tr>
								<tr>
									<td colspan="3">


										<div class="div_btn" >
											<input type="radio"  name="colbtn" id="btn92_1" value="01">
											<input type="radio"class = "colbtn" name="colbtn" id="btn92_2" value="02">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_3" value="03">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_4" value="04">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_5" value="05">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_6" value="06">
											<input type="radio" class = "colbtn"  name="colbtn" id="btn92_7" value="07">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_8" value="08">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_9" value="09">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_10" value="10">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_11" value="11">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_12" value="12">
											<input type="radio" class = "colbtn" name="colbtn" id="btn92_13" value="13">
										</div> <br>
									</td>
								</tr>


								<tr>
									<td align="center">FEED</td>
									<!-- <td align="left" class="td1"> 
									<input type="time" class="feed" id="feed" name = "select"> 
									</td>-->
									<td colspan="2" align="left" class="td1">
										<div class="selectbox">
											<label for="seleect"><%=sdto.getSet_feed()%>시간</label> <select id="select" name="feed" >
												<option value = "3">3시간</option>
												<option value = "6">6시간</option>
												<option value = "9">9시간</option>
												<option value = "12">12시간</option>
											</select>
										</div>
									</td>
<!-- 									<td><input type = "button" value = "시간등록" id="timeselec"></td> -->
								</tr>
								<tr>
									<td align="center">TEMP</td>
									<td align="center"><input type="text" class="textsm"
										id="temp" name="temp" value="<%=sdto.getSet_temp()%>"></td>
									<td align="left"><sup>o</sup>C</td>
								</tr>
								<tr>
									<td align="center">LEVEL</td>
									<td align="center"><input type="text" class="textsm"
										id="level" name="level" value="<%=sdto.getSet_level()%>"></td>
									<td align="left">cm</td>
								</tr>

								<tr>
									<td colspan="3"><br></td>

								</tr>
								<tr>
									<td colspan="3" align="center" class="td1"><input
										type="submit" id="edit" value="적용하기"></td>

								</tr>

							</table>
						</form>
					</div>
				</section>
			</article>

		</div>

		<!-- Footer -->
		<div id="footer">
			<ul class="copyright">
				<li>&copy; Untitled.</li>
				<li>Design: <a href="http://html5up.net">HTML5 UP</a></li>
				<li><a href="<%=ctx%>/logout" id ="logout">로그아웃</a></li>
			</ul>
		</div>

	</div>

	<!-- Scripts -->
	<script src="assets/js/jquery.min.js"></script>

	<script src="assets/js/browser.min.js"></script>
	<script src="assets/js/breakpoints.min.js"></script>
	<script src="assets/js/util.js"></script>
	<script src="assets/js/main.js"></script>
	<script type="text/javascript">



$("#check").click(function(){
	$.ajax({
		url : "<%=ctx%>/level",
		data : 'waterlevel='+<%=wdto.getWaterlevel()%>+'&setlevel='+<%=sdto.getSet_level()%>
		+'&watertemp='+<%=wdto.getWatertemp()%>+'&settemp='+<%=sdto.getSet_temp()%>
		+'&feedpressure='+<%=wdto.getFeedpressure() %>,
		success : function(result){
			/* if(result === "0"){
				$("#ck").html("물이 부족해요! 물을 보충해 주세요. <br> 수온이 낮아 발열패드 작동중입니다.").css("color","tomato");
			}else if(result === "1"){
				$("#ck").html("물이 부족해요! 물을 보충해 주세요.").css("color","tomato");				
			}else if(result === "2"){
				$("#ck").html("수온이 낮아 발열패드 작동중입니다.").css("color","tomato");				
				
			}else if(result === "3"){
				$("#ck").html("쾌적한 상태입니다!").css("color","limegreen");								
			} */
			
			if(result[0] === "0" && result[1] === "0" && result[2] === "0"){
				$("#ck1").html("쾌적한 상태입니다!").css("color","limegreen");
			}
			if(result[0] === "1"){
				$("#ck1").html("물이 부족해요! 물을 보충해 주세요.").css("color","tomato");
			}if(result[1] === "1"){
				$("#ck2").html("수온이 낮아 발열패드 작동중입니다.").css("color","tomato");
			}if(result[2] === "1"){
				$("#ck3").html("먹이통이 비었어요! 먹이를 채워주세요.").css("color","tomato");
			}if(result[2] === "2"){
				$("#ck3").html("먹이통이 열려있어요! 확인해주세요.").css("color","tomato");
			}
			
				
		}
	});


});
<%if (serialCode != null) {%>
$("#alogin").attr('href','#');
<%}%>

<%if(serialCode == null){%>
$("#afish").attr('href','#');
$("#aedit").attr('href','#');
$("#logout").attr('href','#');


<%}%>


$("#toggle-slider").click(function(){
	   $('.div_btn').toggle();
	  
	});
	

	
	$('#login').on('click',function(){
		
		$.ajax({
			// 눈으로 보이는 url에는 변동이 없지만 네트워크상에서는 볼 수 있어서 post방식 필요!
			url : "<%=ctx%>/login.do",
			type : "POST",
			data : 'id='+$('#id').val()+'&pw='+$('#pw').val(),
			success : function(result){
				if(result === "fail"){
					$('#loginck').html("잘못 입력하셨습니다.").css("color","tomato");
				}else{
					// alert("로그인 성공");
			
					window.location.href = "<%=ctx%>/logincheck";
				}
			}
		});
});

		$(function() {
			var selectTarget = $('.selectbox select');

			selectTarget.change(function() {
				var select_name = $(this).children('option:selected').text();
				$(this).siblings('label').text(select_name);
			});

			selectTarget.on({
				'focus' : function() {
					$(this).parent().addClass('focus');
				},
				'blur' : function() {
					$(this).parent().removeClass('focus');
				}
			});

		});
	</script>

</body>
</html>