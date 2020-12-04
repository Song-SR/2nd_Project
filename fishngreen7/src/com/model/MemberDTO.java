package com.model;

public class MemberDTO {
	private String id;
	private String pw;
	private String serialcode;
	private String name;
	
	public MemberDTO() {
		
	}
	
	public MemberDTO(String id, String pw, String serialcode, String name) {
		super();
		this.id = id;
		this.pw = pw;
		this.serialcode = serialcode;
		this.name = name;
	}



	public MemberDTO(String id, String pw) {
		super();
		this.id = id;
		this.pw = pw;
	}



	public MemberDTO(String id, String pw, String name) {
		super();
		this.id = id;
		this.pw = pw;
		this.name = name;
	}

	public String getId() {
		return id;
	}



	public void setId(String id) {
		this.id = id;
	}



	public String getPw() {
		return pw;
	}



	public void setPw(String pw) {
		this.pw = pw;
	}



	public String getSerialcode() {
		return serialcode;
	}



	public void setSerialcode(String serialcode) {
		this.serialcode = serialcode;
	}



	public String getName() {
		return name;
	}



	public void setName(String name) {
		this.name = name;
	}
	
	

}
