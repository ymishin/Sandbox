package com.example.test;

import org.apache.deltaspike.data.api.EntityRepository;
import org.apache.deltaspike.data.api.Query;
import org.apache.deltaspike.data.api.QueryResult;
import org.apache.deltaspike.data.api.Repository;

import javax.enterprise.context.ApplicationScoped;

@ApplicationScoped
@Repository
public interface PersonRepository extends EntityRepository<Person, Long> {

    @Query("from Persons")
    QueryResult<Person> findAllPersons();
}