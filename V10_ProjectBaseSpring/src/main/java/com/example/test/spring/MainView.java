package com.example.test.spring;

import java.util.LinkedHashMap;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;

import com.vaadin.flow.component.UI;
import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.dependency.HtmlImport;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.html.Label;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.data.provider.DataProvider;
import com.vaadin.flow.data.provider.ListDataProvider;
import com.vaadin.flow.data.provider.QuerySortOrder;
import com.vaadin.flow.data.provider.SortDirection;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.theme.Theme;
import com.vaadin.flow.theme.lumo.Lumo;

@Theme(Lumo.class)
@HtmlImport("styles/shared-styles.html")
@Route("")
public class MainView extends VerticalLayout {
	
    private final PersonService service;

	public MainView(PersonService service) {
		this.service = service;
 		
        Grid<Person> grid = new Grid<Person>();
        grid.setColumnReorderingAllowed(true);
        grid.addColumn(Person::getName).setHeader("Name").setResizable(true).setComparator(
        		(item1, item2) -> item1.getName().compareToIgnoreCase(item2.getName()));
        grid.addColumn(Person::getAge).setHeader("Age").setResizable(false).setComparator(
        		(item1, item2) -> item1.getAge().compareTo(item2.getAge()));
        
        DataProvider<Person, Void> dataProvider = DataProvider.fromCallbacks(
                query -> {        	
//                	Map<String, Boolean> sortOrder = new LinkedHashMap<>();
//                    for (QuerySortOrder order : query.getSortOrders()) {
//                    	sortOrder.put(order.getSorted(), order.getDirection().equals(SortDirection.ASCENDING));            	
//                    }
//                    return service.findAll(query.getOffset(), query.getLimit(), sortOrder).stream();
                	return service.findAll().stream();
                },
        		query -> service.count());
        grid.setDataProvider(dataProvider);
        
        Label label = new Label("Not clicked");
        Button button = new Button("Click me", event -> label.setText("Clicked!"));                
        
        add(grid, button, label);       
	}
}