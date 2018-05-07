package com.example.test.spring;

import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class PersonService {

    private final PersonRepository repository;
    
    public PersonService(PersonRepository repository) {
        this.repository = repository;     
        addSomeData();
    }

//    public List<Person> findAll(int offset, int limit, Map<String, Boolean> sortOrders) {
//    	int page = offset / limit;
//        List<Sort.Order> orders = sortOrders.entrySet().stream()
//                .map(e -> new Sort.Order(e.getValue() ? Sort.Direction.ASC : Sort.Direction.DESC, e.getKey()))
//                .collect(Collectors.toList());
//
//        PageRequest pageRequest = new PageRequest(page, limit, orders.isEmpty() ? null : new Sort(orders));
//        List<Person> items = repository.findAll(pageRequest).getContent();
//        return items.subList(offset%limit, items.size());             
//    }

    public List<Person> findAll() {
    	return repository.findAll();
    }
    
    public Integer count() {
        return Math.toIntExact(repository.count());
    }
    
    private void addSomeData() {
        repository.deleteAll();
        repository.save(new Person("John", 10));
        repository.save(new Person("Jack", 20));
        repository.save(new Person("Bill", 30));
        repository.save(new Person("Lars", 40));
        repository.save(new Person("Paul", 50));
    }
}