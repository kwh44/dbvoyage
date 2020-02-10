## DBvoyage

### Intro & Background
We all use Wikipedia in our everyday life to look up some information, but the problem 
arises when your questions become more complex, i.e., how many cities in Germany have 
the population more than 5 million or what cities in Europe were visited the most for the 
last year. In this case, Wikipedia can't give you the answer, because for that it 
needs to look up thousands of articles and analyze the information to find the answer.
Although most of the factual information is present in so-called info-boxes, they are useful
only when a question is related to a single article. So Wikipedia presents by itself the unstructured
(in the form of plain text) and semi-structured (info-boxes, tables, graphs) free source of encyclopedic data.  
And as it transpired the questions, or queries if you will, like the above mentioned are
pretty standard, and so the DBpedia project was created to make all information available from
Wikipedia more structured and to put in such a form that even more complex queries can
be answered quickly by the machine.  
### Mission & Project goal
The DBvoyage project tries to do the same what DBpedia did, but this time with
another source of data, travel data taken from wikivoyage. Wikivoyage data format already
has some structure, so we would be happy that our task is almost done, but that is only on
the surface. The data wikivoyage has semi-structured; it is formed in accord with
what they call it, JSON listing, and as it was discovered, not all contributors strictly follow it.
So here we propose our solution -- DBvoyage.
The current version of DBvoyage managed to extract
1 688 488 [semantic triples](https://en.wikipedia.org/wiki/Semantic_triple). 
In compressed form, all the data has a size of 38.5 MB.
The link to download DBvoyage compressed dump: [dbvoyage.zip](https://drive.google.com/uc?export=download&id=167jzm3NpXkNxOIAxloy8goYDmes5knIh)

### How User Interacts
![uset interaction](/images/interact.png)
With DBvoyage user interacts,
making SPARQL queries or directly referencing URL node in DBvoyage graph to view all triples it has.

### Examples Of Queries And Responses 
![query1](/images/query1.png)
![response1](/images/response1.png)
Also all Wikivoyage information about activities and attractions is present in the DBvoyage graph and can be referenced with URL found in the response.
![node_info](/images/url_node.png)
Example for activity in Aarhus: Bicycle Tour
![bicycle_tour](/images/aarhus_bicycle.png)
![aros](/images/aros.png)

### Architecture Overview
![description](/images/desc.png)

#### Extraction Framework
##### Six extractors are written

* See section
* Do section
* Article abstract
* Cities section
* Region section
* Article title
* Wikivoyage article link

They process all data from wikivoyage XML dump. Next step is transitive closure of
graph from created triples, with at most 12 inner vertices in path. The final step
is serialization of triples in N-Triples format.
#### Virtuoso Server
All triples are loaded to the graph over which SPARQL queries can be executed.
#### HTTP Server
Basic nodejs server providing interface with project information, SPARQL queries
examples and link to editor for writing SPARQL queries over dbvoyage graph.
##### The server is running and available at [DBvoyage](http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/")
View all info DBvoyage has about
[Lviv Opera and Ballet National Academic Theatre](http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/attraction/Lviv%20Opera%20and%20Ballet%20National%20Academic%20Theatre)

In order to view all attractions DBvoyage knows are located in Ukraine:
Go to  [SPARQL Editor](http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/sparql)
and write the following query
```sql
select
    ?attractions
where
{
<http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/article/Ukraine>
<http://ec2-52-15-243-121.us-east-2.compute.amazonaws.com/ontology/property/hasAttraction>
?attractions
}
```

