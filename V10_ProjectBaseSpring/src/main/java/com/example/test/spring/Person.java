package com.example.test.spring;

import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Column;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

@Entity
@Table(name = "Persons")
public class Person {
	
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private Long id;
	
    @Column(name = "Name")
    private String name;
    
    @Column(name = "Age")
    private int age;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }
    
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getAge() {
        return age;
    }
    
    public void setAge(int age) {
    	this.age = age;
    }
	
	Person(String name, int age)
	{
		this.name = name;
		this.age = age;		
	}
	
	Person()
	{	
	}
}