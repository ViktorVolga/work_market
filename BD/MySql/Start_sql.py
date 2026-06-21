#!/usr/bin/env python3
import mysql.connector

#mysql --host=0.0.0.0 --user=root --password=12345 --port=3311
#mysql --host=0.0.0.0 --user=work_market_db --password=98765 --port=3311

cnx = mysql.connector.connect(user='root', 
                              password='12345',
                              host='127.0.0.1',
                              port=3311)

def table_exists(table_name): 
  cursor.execute(f"SELECT COUNT(*) FROM information_schema.tables WHERE table_name = '{table_name}';")
  result = cursor.fetchone()[0]  
  return result > 0

def dtb_exists(dtb_name): 
  cursor.execute(f"SHOW DATABASES LIKE '{dtb_name}';")
  result = cursor.fetchone()  
  return result is not None

cursor = cnx.cursor()

if dtb_exists('work_market_vacansies'):
  print('work_market_vacansies exists')
else:
  cursor.execute('CREATE DATABASE work_market_vacansies')  
  print('dtb work_market_vacansies created now')

cursor.execute('USE work_market_vacansies')


if not table_exists('countries'):
  print('create table countries')
  cursor.execute("""
    CREATE TABLE countries (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL
               )
    """)
else:
  print('table countries exists')

if not table_exists('cities'):
  print('create table cities')
  cursor.execute("""
    CREATE TABLE cities (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    country_id INT REFERENCES countries(id)
               )
  """)
else:
  print('table cities exists')

if not table_exists('company'):
  print('create table company')
  cursor.execute("""
    CREATE TABLE company (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL
               )
  """)
else:
  print('table company exists')

if not table_exists('companies'):  
  cursor.execute("""
    CREATE TABLE companies (
    id INT AUTO_INCREMENT PRIMARY KEY,
    city_id INT,
    company_id INT,
    CONSTRAINT fk_city_id FOREIGN KEY (city_id) REFERENCES cities(id),
    CONSTRAINT fk_company_id FOREIGN KEY (company_id) REFERENCES company(id)
               )
  """)
  print('table companies created')
else:
  print('table companies exists')

if not table_exists('vacancy'):  
  cursor.execute("""
    CREATE TABLE vacancy (
    id INT AUTO_INCREMENT PRIMARY KEY,
    external_id INT UNIQUE,
    name VARCHAR(255) NOT NULL,
    description TEXT,
    is_actual BOOLEAN
              )
  """)
  print('table vacancy created')
else:
  print('table vacancy exists')

if not table_exists('vacancies'):  
  cursor.execute("""
    CREATE TABLE vacancies (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vacancy_id INT,
    company_id INT,
    CONSTRAINT fk_vacancy_id FOREIGN KEY (vacancy_id) REFERENCES vacancy(id),
    CONSTRAINT fk_vcompany_id FOREIGN KEY (company_id) REFERENCES company(id)
               )
  """)
  print('table vacancies created')
else:
  print('table vacancies exists')

if not table_exists('skill'):  
  cursor.execute("""
    CREATE TABLE skill (
    id INT PRIMARY KEY,
    name VARCHAR(255) NOT NULL    
              )
  """)
  print('table skill created')
else:
  print('table skill exists')

if not table_exists('vacancy_skills'):  
  cursor.execute("""
    CREATE TABLE vacancy_skills (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vacancy_id INT,
    skill_id INT,
    CONSTRAINT fk_svacancy_id FOREIGN KEY (vacancy_id) REFERENCES vacancy(id),
    CONSTRAINT fk_skill_id FOREIGN KEY (skill_id) REFERENCES skill(id)   
              )
  """)
  print('table vacancy_skills created')
else:
  print('table vacancy_skills exists')

if not table_exists('salary'):  
  cursor.execute("""
    CREATE TABLE salary (
    id INT AUTO_INCREMENT PRIMARY KEY,
    _from INT,
    _to INT
              )
  """)
  print('table salary created')
else:
  print('table salary exists')

if not table_exists('vacancy_salary'):  
  cursor.execute("""
    CREATE TABLE vacancy_salary (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vacancy_id INT,
    salary_id INT,
    CONSTRAINT fk_vs_vacancy_id FOREIGN KEY (vacancy_id) REFERENCES vacancy(id),
    CONSTRAINT fk_salary_id FOREIGN KEY (salary_id) REFERENCES salary(id) 
              )
  """)
  print('table vacancy_salary created')
else:
  print('table vacancy_salary exists')

if not table_exists('skill_salary'):  
  cursor.execute("""
    CREATE TABLE skill_salary (
    id INT AUTO_INCREMENT PRIMARY KEY,
    skill_id INT,
    salary_id INT,
    CONSTRAINT fk_ss_skill_id FOREIGN KEY (skill_id) REFERENCES skill(id),
    CONSTRAINT fk_ss_salary_id FOREIGN KEY (salary_id) REFERENCES salary(id) 
              )
  """)
  print('table skill_salary created')
else:
  print('table skill_salary exists')

if not table_exists('requirements'):  
  cursor.execute("""
    CREATE TABLE requirements (
    id INT AUTO_INCREMENT PRIMARY KEY,
    applicant_level VARCHAR(255) NOT NULL,
    expirience VARCHAR(255) NOT NULL
              )
  """)
  print('table requirements created')
else:
  print('table requirements exists')

if not table_exists('vacancy_requirements'):
  cursor.execute("""
    CREATE TABLE vacancy_requirements (
    id INT AUTO_INCREMENT PRIMARY KEY,
    vacancy_id INT,
    requirements_id INT,
    CONSTRAINT fk_vr_vacancy_id FOREIGN KEY (vacancy_id) REFERENCES vacancy(id),
    CONSTRAINT fk_vr_requirements_id FOREIGN KEY (requirements_id) REFERENCES requirements(id) 
              )
  """)
  print('table vacancy_requirements created')
else:
  print('table vacancy_requirements exists')

if not table_exists('skill_requirements'):
  cursor.execute("""
    CREATE TABLE skill_requirements (
    id INT AUTO_INCREMENT PRIMARY KEY,
    skill_id INT,
    requirements_id INT,
    CONSTRAINT fk_sr_vacancy_id FOREIGN KEY (skill_id) REFERENCES skill(id),
    CONSTRAINT fk_sr_requirements_id FOREIGN KEY (requirements_id) REFERENCES requirements(id) 
              )
  """)
  print('table skill_requirements created')
else:
  print('table skill_requirements exists')

if not table_exists('salary_requirements'):
  cursor.execute("""
    CREATE TABLE salary_requirements (
    id INT AUTO_INCREMENT PRIMARY KEY,
    salary_id INT,
    requirements_id INT,
    CONSTRAINT fk_sar_salary_id FOREIGN KEY (salary_id) REFERENCES salary(id),
    CONSTRAINT fk_sar_requirements_id FOREIGN KEY (requirements_id) REFERENCES requirements(id) 
              )
  """)
  print('table salary_requirements created')
else:
  print('table salary_requirements exists')

if not table_exists('unknown_cities'):
  cursor.execute("""
    CREATE TABLE unknown_cities (
    id INT AUTO_INCREMENT PRIMARY KEY,
    city VARCHAR(255) NOT NULL   
              )
  """)
  print('table unknown_cities created')
else:
  print('table unknown_cities exists')

cursor.close()
cnx.close()

exit()







