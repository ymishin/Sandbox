package com.example.test;

public class Item {
	
    private String name;
    private int age;
    
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
	
	Item(String name, int age)
	{
		this.name = name;
		this.age = age;		
	}
}