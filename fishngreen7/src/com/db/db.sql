create table member(
id varchar2(20),
pw varchar2(20),
serialcode varchar2(20),
name varchar2(20));

create sequence serial_seq;
drop sequence serial_seq;
select * from member;

drop table member cascade constraints;

create table water(
serialcode varchar2(20),
watertemp varchar2(10),
waterlevel varchar2(10),
led_power varchar2(4),
color varchar2(4),
feedpressure varchar2(10),
feeding varchar2(4),
feedtime date);  -- 가장 마지막 먹이공급시간을 저장.

insert into member values('lee','1234','0','관리자');

insert into water values('15','23','17','ON','0','0','OFF',sysdate);
insert into water values('0','25','25','OFF','0','0','OFF', sysdate);
update water set watertemp = '100' where serialcode='5';
select * from water;
drop table water;

select to_char(feedtime, 'MM-DD HH24:mi') from water;

update water set feedtime = sysdate where sysdate >= feedtime + (10/24/60);
-- ex) 가장 마지막 먹이공급시간으로부터 10분이 지났으면 먹이공급시간 새롭게 저장하면서 먹이공급 on

create table setting(
serialcode varchar2(20),
set_temp varchar2(10),
set_level varchar2(10),
set_power varchar2(4),
set_color varchar2(4),
set_feed varchar2(20));

select * from setting;
drop table setting;