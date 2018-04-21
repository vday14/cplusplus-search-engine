C++lue Search Engine ReadME:::

Operating system:
Mac OSX (should work on Linux as well but not as thoroughly tested)

In order to run the server and interact with the UI:
---------------------------------------------------
Run the `server` exectuable, specifying port number and `/bootstrap_landing_page` as command line arguments
In your web browser use the url: `localhost:{portnumbe}/index.html`
Example --> 
Command Line = `7000 /bootstrap_landing_page`
URL in browser = `localhost:7000/index.hml`

If you are on MWireless:
Use IP address instead of local host
Example URL in browser = `{ip address}:7000/index.hml`

*** if you recieve an error `Assertion failed: (bindResult == 0)` change the port number to a differnt port

In order to run the search engine through the terminal:
---------------------------------------------------
Run the `search-engine` executable.
In the `indexer/IndexerConstants.h` file, ensure the index is using `/build50/`