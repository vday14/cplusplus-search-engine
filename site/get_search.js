$(function () {

    $("#search").click(get_request);



});




function get_request(artist_name){
    $query = $("#query").val();
    console.log("Making a query");

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

        }
    });


};