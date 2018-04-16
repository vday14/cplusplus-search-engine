$(function () {

    $("#search").click(get_request);
    $("#lucky").click(feeling_lucky);



});


function feeling_lucky(){
//open first link
    $query = $("#query").val();
    console.log("Making a query: ");
    console.log($query);

    $.ajax({
        url: "/search",
        type: 'GET',
        contentType: "text/plain",
        data: $query,
        dataType: 'text/plain',
        success: function (data) {

        },
        error: function (data) {
            console.log("error");
            console.log(data.responseText);
            var dataReturned = data.responseText;
            var returnedJSON = JSON.parse(data.responseText);
            var results = returnedJSON['results'];
            var topResultUrl = results[0]['site'];
            console.log("Top URL: " + topResultUrl);
            window.open("https://" + topResultUrl, '_blank');

        }
    });

}



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

        },
        error: function (data) {
            console.log("error");
            console.log(data.responseText);
            var dataReturned = data.responseText;
            var returnedJSON = JSON.parse(data.responseText);
            var results = returnedJSON['results'];
            var total_results = returnedJSON['total_results'];
            var time = returnedJSON['time'];

            $("#timeToRun").text("Time to run :     " +  time);
            $("#totalResults").text("Total Results Found:     "  + total_results);


            $("#results").empty();
            $(results).each(function(index, result) {
                var score = result['score'];
                var title = result['title'].replace('#x27;s', ' ');
                var url = result['site'];
                var text = "Score: " + result['score'] + "    :  " + result['title'];
                var title_div = $("<h3 class = 'title'>").text(title);
                var link = $("<div>").html( $("<a>").attr("href", "https://" + url).attr("class", "result").attr( "target", "_blank").text( url ));
                var score = $("<h6 class = 'score'>").text("Scored by engine: " + score);

                link.appendTo(title_div);
                score.appendTo(title_div);
                title_div.appendTo('#results');


            });


        }
    });


};