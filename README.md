# CPP-Simple-Equity-ESG
This is a very simple template of what an generic insurer's Economic Scenario Generator for Equities should ressemble. Using xlwings it is possible to link this implementation 
to Excel for a workable solution. 

Note that I'm using Windows Visual Studio 2019.

## Update
Much of the addition has been in:

1) Creating a matrix class for linear algebra operations
2) Construction of Model and Security Interfaces allowing for pricing different instruments under different models
3) Projection: Simple Monte Carlo price generator

To be done:
1) Finalize inversion of the Jacobian: (Minimization algorithm)
2) Addition of a second Model (Heston preferably)
3) Addition of more complex assets (Enrich the number of assets)
Please feel free to add on to the project if interested! :)
