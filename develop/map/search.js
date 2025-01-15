var univ_json = null;

function searchClickEvent() {
    univ_name = document.getElementsByName("univ_name")[0].value

    let url = "university.json"

    if(univ_json == null) {
        $.ajax({
            url: url,
            type: "get",
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
    for(let i = 0; i < univ_json.length; i++) {
        if(univ_json[i]["학교명"].includes(univ_name)) {
            $("#univ_list").append(`<li onclick="document.getElementById('map').src='index.html?latitude=${univ_json[i]["위도"]}&longitude=${univ_json[i]["경도"]}';">
                    ${univ_json[i]["학교명"]}
            </li>`)
        }
        
    }
}