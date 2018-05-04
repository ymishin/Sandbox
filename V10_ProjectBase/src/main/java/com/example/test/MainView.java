package com.example.test;

import java.util.LinkedHashMap;
import java.util.Map;

import javax.inject.Inject;

import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.dependency.HtmlImport;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.html.Label;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.data.provider.DataProvider;
import com.vaadin.flow.data.provider.QuerySortOrder;
import com.vaadin.flow.data.provider.SortDirection;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.theme.Theme;
import com.vaadin.flow.theme.lumo.Lumo;

@Theme(Lumo.class)
@HtmlImport("styles/shared-styles.html")
@Route("")
public class MainView extends VerticalLayout {
	
	private static final long serialVersionUID = -1598327145600728556L;
	
	@Inject
    private PersonService service;

    public MainView() {
//        ExampleTemplate template = new ExampleTemplate();
//    	  Button button = new Button("Click me", event -> template.setValue("Clicked!"));        
//        add(button, template);
//        setClassName("main-layout");
    	           
        Grid<Person> grid = new Grid<Person>();
        grid.setColumnReorderingAllowed(true);
        grid.addColumn(Person::getName).setHeader("Name").setResizable(true).setComparator(
        		(item1, item2) -> item1.getName().compareToIgnoreCase(item2.getName()));
        grid.addColumn(Person::getAge).setHeader("Age").setResizable(false).setComparator(
        		(item1, item2) -> item1.getAge().compareTo(item2.getAge()));
        
//        grid.setItems(service.getSomePersons());
//        ListDataProvider<Person> dataProvider = DataProvider.ofCollection(service.getSomePersons());
        
        DataProvider<Person, Void> dataProvider = DataProvider.fromCallbacks(
                query -> {        	
                	Map<String, Boolean> sortOrder = new LinkedHashMap<>();
                    for (QuerySortOrder order : query.getSortOrders()) {
                    	sortOrder.put(order.getSorted(), order.getDirection().equals(SortDirection.ASCENDING));            	
                    }
                    return service.findAll(query.getOffset(), query.getLimit(), sortOrder).stream();
                },
        		query -> service.count());
        grid.setDataProvider(dataProvider);
        
        Label label = new Label("Not clicked");
        Button button = new Button("Click me", event -> label.setText("Clicked!"));                
        add(grid, button, label);
    }
}
