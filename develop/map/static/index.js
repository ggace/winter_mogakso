urlSearch = new URLSearchParams(location.search);
latitude = urlSearch.get('latitude')
longitude = urlSearch.get('longitude')
level = 3

if(latitude == null || longitude == null) {
    console.log("Nan yes")
    latitude = 36.2253017
    longitude = 127.6460516
    level = 13
    var mapOption = { 
        center: new kakao.maps.LatLng(latitude, longitude), // 지도의 중심좌표
        level: level // 지도의 확대 레벨
    };
    
}
else {
    console.log("Nan no")
    var mapOption = { 
        center: new kakao.maps.LatLng(parseFloat(latitude), parseFloat(longitude)), // 지도의 중심좌표
        level: level // 지도의 확대 레벨
    };
}

console.log(latitude)

var mapContainer = document.getElementById('map') // 지도를 표시할 div 


var map = new kakao.maps.Map(mapContainer, mapOption);

var clusterer = new kakao.maps.MarkerClusterer({
    map: map,
    gridSize: 50,
    averageCenter: true,
    minLevel: 6,
    disableClickZoom: true,
    styles: [{
        width : '53px', height : '52px',
        background: 'url("/static/resources/cluster.png") no-repeat',
        backgroundSize: "cover",
        color: '#fff',
        textAlign: 'center',
        lineHeight: '54px',
    }]
});

$.ajax({
    url:"/university.json",
    type: "get",
    dataType: "json",
    async: true,
    success: function(result) {
        
        
        var imageSrc = "/static/resources/marker.png"; 
        var imageSize = new kakao.maps.Size(30, 45); 
        var markerImage = new kakao.maps.MarkerImage(imageSrc, imageSize); 
        for (var i = 0; i < result.length; i++) {
            let position = {
                title: result[i]["학교명"],
                latlng: new kakao.maps.LatLng(result[i]["위도"], result[i]["경도"])
            }

            var infowindow = new kakao.maps.InfoWindow({
                content: `
                <div style="padding: 10px; height: 100px; width: 250px">
                    <div style="font-size: 15px">
                        ${result[i]["학교명"]}
                    </div>
                    <div style="font-size: 10px">
                        ${result[i]["우편번호"]} ${result[i]["도로명주소"]}
                    </div>

                </div>
                `,
                removable: true
            });

            
            var marker = new kakao.maps.Marker({
                map: map, 
                position: position.latlng, 
                title : position.title, 
                image : markerImage,
                text: result
            });
            kakao.maps.event.addListener(marker, 'click', makeClickListener(map, marker, infowindow, i));
            clusterer.addMarker(marker);            
        }
        clusterer.setTexts(function( size ) {
            var text = '';
        
            text = size.toString()
        
            return text;
        });

        
    }
});
// 일반 지도와 스카이뷰로 지도 타입을 전환할 수 있는 지도타입 컨트롤을 생성합니다
var mapTypeControl = new kakao.maps.MapTypeControl();

// 지도에 컨트롤을 추가해야 지도위에 표시됩니다
// kakao.maps.ControlPosition은 컨트롤이 표시될 위치를 정의하는데 TOPRIGHT는 오른쪽 위를 의미합니다
map.addControl(mapTypeControl, kakao.maps.ControlPosition.TOPRIGHT);

// 지도 확대 축소를 제어할 수 있는  줌 컨트롤을 생성합니다
var zoomControl = new kakao.maps.ZoomControl();
map.addControl(zoomControl, kakao.maps.ControlPosition.RIGHT);

kakao.maps.event.addListener(clusterer, 'clusterclick', function(cluster) {

    // 현재 지도 레벨에서 1레벨 확대한 레벨
    var level = map.getLevel()-3;
    
    // 지도를 클릭된 클러스터의 마커의 위치를 기준으로 확대합니다
    map.setLevel(level, {anchor: cluster.getCenter()});
})

// 인포윈도우를 표시하는 클로저를 만드는 함수
function makeClickListener(map, marker, infowindow) {
    return function() {
        infowindow.open(map, marker);
    };
}

let infowindow_trigger;
    
// 인포윈도우를 닫는 클로저를 만드는 함수
function makeClickListener(map, marker, infowindow, index) {
    return function() {
        if(infowindow_trigger === infowindow) {
            infowindow.close();
            infowindow_trigger = null;
            return;
        }
        else if(infowindow_trigger){
            infowindow_trigger.close();
            infowindow_trigger = null;
        }
        infowindow.open(map, marker)
        infowindow_trigger = infowindow
        
    };
}