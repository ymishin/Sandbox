package com.example.test;

import java.util.LinkedList;

import com.vaadin.flow.component.button.Button;
import com.vaadin.flow.component.dependency.HtmlImport;
import com.vaadin.flow.component.grid.Grid;
import com.vaadin.flow.component.html.Label;
import com.vaadin.flow.component.orderedlayout.VerticalLayout;
import com.vaadin.flow.router.Route;
import com.vaadin.flow.theme.Theme;
import com.vaadin.flow.theme.lumo.Lumo;

/**
 * The main view contains a button and a template element.
 */
@Theme(Lumo.class)
@HtmlImport("styles/shared-styles.html")
@Route("")
public class MainView extends VerticalLayout {

    public MainView() {
//        ExampleTemplate template = new ExampleTemplate();
//    	  Button button = new Button("Click me", event -> template.setValue("Clicked!"));        
//        add(button, template);
//        setClassName("main-layout");
    	           
        Grid<Item> grid = new Grid<Item>();
        grid.setColumnReorderingAllowed(true);
        grid.addColumn(Item::getName).setHeader("Name").setResizable(true).setComparator(
        		(item1, item2) -> item1.getName().compareToIgnoreCase(item2.getName()));
        grid.addColumn(Item::getAge).setHeader("Age").setResizable(false).setComparator(
        		(item1, item2) -> item1.getAge().compareTo(item2.getAge()));
        grid.setItems(getItems());                       
        Label label = new Label("Not clicked");
        Button button = new Button("Click me", event -> label.setText("Clicked!"));                
        add(grid, button, label);
    }
    
    LinkedList<Item> getItems()
    {
        LinkedList<Item> items = new LinkedList<Item>();
        items.add(new Item("John", 10));
        items.add(new Item("Jack", 20));
        items.add(new Item("Bill", 30));
        items.add(new Item("Hue", 40));
        items.add(new Item("Paul", 50));        
        return items;
    }
}
