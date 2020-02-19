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
another source of data, travel data taken from Wikivoyage. Wikivoyage data format already
has some structure, so we would be happy that our task is almost done, but that is only on
the surface. The data Wikivoyage has semi-structured; it is formed in accord with
what they call it, JSON listing, and as it was discovered, not all contributors strictly follow it.
So here we propose our solution -- DBvoyage.

### How user interacts
![uset interaction](/images/interact.png)
With DBvoyage user interacts,
making SPARQL queries or directly referencing URL node in DBvoyage graph  
to view all triples it has.

### Examples of queries and responses 
![query1](/images/query1.png)
![response1](/images/response1.png)
Also all Wikivoyage information about activities and attractions is present in the DBvoyage graph and can be referenced with URL found in the response.
![node_info](/images/url_node.png)
Example for activity in Aarhus: Bicycle Tour
![bicycle_tour](/images/aarhus_bicycle.png)
Example for attraction in Aarhus: ARoS
![aros](/images/aros.png)

### Architecture overview
![description](/images/desc.png)

#### Extraction framework
##### Six extractors are written
* See section
* Do section
* Article abstract
* Cities section
* Region section
* Article title
* Wikivoyage article link  

They process all data from Wikivoyage XML dump. Next step is transitive closure of
graph from created triples, with at most 12 inner vertices in path. The final step
is serialization of triples in N-Triples format.
#### Virtuoso server
All triples are loaded to the graph over which SPARQL queries can be executed.
#### HTTP server
Basic nodejs server providing interface with project information, SPARQL queries
examples and link to editor for writing SPARQL queries over dbvoyage graph.  
### SPARQL query snippet
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

### Known issues
* It needs a significant amount of time to compute the partial transitive closure of DBvoyage. In essence, it tries to create the relation between node A and node C, if node C is reachable from A by going through no more than n intermediate nodes. For example, France has Paris, Paris has Eiffel Tower; therefore we need to create the connection between node France and node Eiffel Tower, but this task becomes more compute-heavy when the number of intermediate nodes goes from one to five or ten, for such task no better than O(n^3) algorithm exists. 
  Optimization of this task would significantly improve the time needed to update existing nodes and connections between them in case of the publication of the article about a new country/city/place.
* For some section of JSON listings the article writers made it very hard to develop the extractor that generalizes for all articles: 
  unknowable usage of the tabs, different ways of formatting the tabular information and URLs, and other cases of deviating from the Wikivoyage JSON listing format were making Virtuoso complain about the triples not conforming to any of the known RDF serialization standards. 
   
### Results
The current version of DBvoyage managed to extract
1 688 488 [semantic triples](https://en.wikipedia.org/wiki/Semantic_triple). 
In compressed form, all the data has a size of 38.5 MB.
The link to download DBvoyage compressed dump: [dbvoyage.zip](https://drive.google.com/uc?export=download&id=167jzm3NpXkNxOIAxloy8goYDmes5knIh)



### Next steps
* UI/UX of the DBvoyage can be improved: design of homepage, SPARQL editor and SPARQL response page
* Improvement of the quality of existing extractors
* Addition of the extractors for other sections of Wikivoyage JSON listings
* Improvement of the relevance of the connections between the graph vertices created by running transitive closure
* Optimization of the time needed for running transitive closure on the DBvoyage graph

### How you can contribute
Feel free to create pull requests with any tasks accomplished related to the steps described above.  
