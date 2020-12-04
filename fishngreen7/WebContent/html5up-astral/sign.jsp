<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="UTF-8"%>
<!DOCTYPE HTML>
<!--
   Astral by HTML5 UP
   html5up.net | @ajlkn
   Free for personal and commercial use under the CCA 3.0 license (html5up.net/license)
-->
<html>
   <head>
      <title>29동성</title>
      <meta charset="utf-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no" />
      <link rel="stylesheet" href="assets/css/main.css" />
      <noscript><link rel="stylesheet" href="assets/css/noscript.css" /></noscript>
      
      <style type="text/css">
         #aSign{
            font-size : 20px;
         
         }
      </style>
   </head>
   <body class="is-preload">

	<% 
	String ctx = request.getContextPath();
	request.setCharacterEncoding("UTF-8");
	response.setCharacterEncoding("UTF-8");
	%>

      <!-- Wrapper-->
         <div id="wrapper">

            <!-- Nav -->
               <nav id="nav">
               
                  <a href="#" class="fas fa-user-plus"><span>SIGN</span></a>
                  
               </nav>

            <!-- Main -->
               <div id="main">

                  <!-- Contact -->
                     <article id="contact" class="panel">
                        <header>
                           <h2>SIGN</h2>
                        </header>
                        <form action="<%=ctx %>/sign.do" method="post"> <!-- 나중에 서블릿만들어서 데이터 전송해야함 -->
                           <div>
                              <div class="row">
                              <div class="col-12">
                                    <input type="text" name="name" placeholder="이름입력" id="name" /></div>
                                 <div class="col-6 col-12-medium">
                                    <input type="text" name="id" placeholder="ID" id="id" />
                                 </div>
                                 <div class="col-6 col-12-medium" align = "right">
                                 <span id = "span92"> </span>
                                    <input type = "button" value = "중복확인" id = "btn92"></div>
                                 
                                 <div class="col-12">
                                    <input type="password" name="pw" placeholder="PASSWORD" id="pw" />
                                 </div>
                                  
                                  <div class="col-6 col-12-medium" align = "right">
                                    <input type="submit" value="회원가입"/></div>
                                    <div class="col-6 col-12-medium" align = "right">
                                    <a href = "./index.jsp">home</a></div>
                                 
                                     
                              </div>
                           </div>
                        </form>
                     </article>

               </div>

            <!-- Footer -->
               <div id="footer">
                  <ul class="copyright">
                     <li>&copy; Untitled.</li><li>Design: <a href="http://html5up.net">HTML5 UP</a></li>
                  </ul>
               </div>

         </div>

      <!-- Scripts -->
         <script src="assets/js/jquery.min.js"></script>
         <script src="assets/js/browser.min.js"></script>
         <script src="assets/js/breakpoints.min.js"></script>
         <script src="assets/js/util.js"></script>
         <script src="assets/js/main.js"></script>

      <!-- 희정 만든 스크립트! -->
   
<script type="text/javascript">
$('#btn92').on('click',function(){
	
	$.ajax({
		// 눈으로 보이는 url에는 변동이 없지만 네트워크상에서는 볼 수 있어서 post방식 필요!
		url : "<%=ctx %>/check.do",
		type : "POST",
		data : 'id='+$('#id').val(),
		success : function(result){
			console.log('요청성공');
			console.log(result);
			if(result == 1){
				//컨텐츠를 넣기!
				$('#span92').html("중복된 아이디 입니다.").css("color","tomato");
				
			}else if(result == 0){
 				
				$('#span92').html("사용가능한 아이디 입니다.").css("color","limegreen");
			}
			
		}
		
	});
	
});
      </script>
   </body>
</html>