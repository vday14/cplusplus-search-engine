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
            var results = data.responseText.split(',');
            $("#results").empty();

            for(r in results)
            {
                var result = $( "<a href='"+ results[r]   +"' id='result1'>" + results[r] + "</a>" );
                $("#results").append(result);

            }


        }
    });


};