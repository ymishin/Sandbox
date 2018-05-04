package com.example.test;

import org.apache.deltaspike.data.api.QueryResult;

import javax.enterprise.context.ApplicationScoped;
import javax.inject.Inject;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

@ApplicationScoped
public class PersonService {

    @Inject
    private PersonRepository repository;

    public List<Person> findAll(int offset, int limit, Map<String, Boolean> sortOrders) {
        QueryResult<Person> result = repository.findAllPersons();
        result.firstResult(offset).maxResults(limit);
        sortOrders.entrySet().stream().forEach(order -> {
            if (order.getValue()) {
                result.orderAsc(order.getKey());
            } else {
                result.orderDesc(order.getKey());
            }
        });
        return result.getResultList();
    }
    
    public int count() {
        return Math.toIntExact(repository.count());
    }
    
    public List<Person> getSomePersons() {
        List<Person> items = new LinkedList<Person>();
        items.add(new Person("John", 10));
        items.add(new Person("Jack", 20));
        items.add(new Person("Bill", 30));
        items.add(new Person("Hue", 40));
        items.add(new Person("Paul", 50));
        return items;
    }
}