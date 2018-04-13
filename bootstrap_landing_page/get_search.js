$(function () {

    $("#search").click(get_request);



});




function get_request(){
    $query = $("#query").val();
    console.log("Making a query: ");
    console.log($query);

    $.ajax({
        url: "/search",
        type: 'GET',
        contentType: "text/plain",
        data:  $query,
        dataType: 'text/plain',
        success: function (data) {


            console.log("Pass");
            console.log("Data")


        },
        error: function (data) {
            console.log("error");
            console.log(data.responseText);
            var dataReturned = data.responseText;
            var returnedJSON = JSON.parse(data.responseText);
            var results = returnedJSON['results'];
            var total_results = returnedJSON['total_results'];
            var time = returnedJSON['time'];

            $("#timeToRun").text("Time to run : " +  time);
            $("#totalResults").text("Total Results Found: "  + total_results);


            $("#results").empty();
            $(results).each(function(index, result) {

                var text = "Score: " + result['score'] + "    :  " + result['site'];

                $("<li/>").html($("<a>").attr("href", "https://" + result['site']).attr("class", "result").attr( "target", "_blank").text( text )).appendTo('#results');
            });
            /*

            for(count in results)
            {
                var result = $( "< a href='"+ results[count]   +"' class='result'" + count + " >" + results[count] + "</a>" );

                $("#results").append(result);

            }
            */


        }
    });


};