var univ_json = null;

function searchClickEvent() {
    univ_name = document.getElementsByName("univ_name")[0].value

    let url = "/university.json"

    if(univ_json == null) {
        $.ajax({
            url: url,
            type: "get",
            dataType: "json",
            async: true,
            success: function(result) {
                univ_json = result;
                
                search(univ_name)
            }
        })
    }
    else {
        search(univ_name)
    }
    
}

function search(univ_name) {
    $("#univ_list").empty()
    let size = 0;
    for(let i = 0; i < univ_json.length && size <= 1000; i++) {
        if(univ_json[i]["학교명"].trim().replaceAll(' ', '').includes(univ_name.trim().replaceAll(' ', ''))) {
            $("#univ_list").append(`<li class="button mx-2" onclick="document.getElementById('map').src='/?latitude=${univ_json[i]["위도"]}&longitude=${univ_json[i]["경도"]}'; $('#map').focus()">
                    ${univ_json[i]["학교명"]}
            </li>`)
            size++;
        }
        
    }

    if(size != 0)
        $("#search-input").val("")
}