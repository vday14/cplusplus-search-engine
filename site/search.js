$(function () {

    $("#search").click(get_request);



});




function get_request(artist_name){
    $query = $("#query").val();


    $.ajax({
        url: "/search",
        type: 'GET',
        contentType: "text/plain",
        data:  $query,
        dataType: 'json',
        success: function (data) {


            console.log("Pass");
            console.log("Data")


        },
        error: function (data) {
            console.log(data);

        }
    });


};