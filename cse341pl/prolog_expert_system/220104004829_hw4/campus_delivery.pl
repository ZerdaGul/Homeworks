% Places
place(admin_office, 1).
place(library, 2).
place(eng_building, 3).
place(lecture_hall_a, 4).
place(cafeteria, 5).
place(inst_y, 6).
place(inst_x, 7).
place(social_sciences_bld, 8).

% Connections and travel times
route(admin_office, cafeteria, 4).
route(admin_office, library, 1).
route(admin_office, eng_building, 3).
route(eng_building, lecture_hall_a, 2).
route(eng_building, library, 5).
route(lecture_hall_a, inst_y, 3).
route(inst_y, library, 3).
route(library, cafeteria, 5).
route(library, social_sciences_bld, 2).
route(cafeteria, social_sciences_bld, 2).
route(social_sciences_bld, inst_x, 8).
route(cafeteria, admin_office, 4).
route(library, admin_office, 1).
route(eng_building, admin_office, 3).
route(lecture_hall_a, eng_building, 2).
route(library, eng_building, 5).
route(inst_y, lecture_hall_a, 3).
route(library, inst_y, 3).
route(cafeteria, library, 5).
route(social_sciences_bld, library, 2).
route(social_sciences_bld, cafeteria, 2).
route(inst_x, social_sciences_bld, 8).

% You can add more facts as needed for the delivery personnel and objects.
% For example:
% delivery_person(person_id, capacity, work_hours, current_job, current_location).
% delivery_object(object_id, weight, pick_up_place, drop_off_place, urgency, in_transit_delivery_person).


% Example delivery personnel
delivery_person(1, 10, 12, 1, admin_office).
delivery_person(2, 15, 16, none, eng_building).
delivery_person(3, 12, 20, none, cafeteria).

% Example delivery objects
delivery_object(1, 3, library, cafeteria, low, none).
delivery_object(2, 5, admin_office, inst_x, medium, none).
delivery_object(3, 2, lecture_hall_a, cafeteria, high, 1). % In transit by person with ID 1
delivery_object(4, 7, cafeteria, inst_x, medium, none).
delivery_object(5, 4, social_sciences_bld, library, low, none).

% Aciliyet kontrolü
is_delivery_urgent(high, _) :- !.
is_delivery_urgent(medium, high) :- !.
is_delivery_urgent(medium, medium) :- !.
is_delivery_urgent(low, high) :- !.
is_delivery_urgent(low, medium) :- !.
is_delivery_urgent(low, low).

% Yerler arasındaki tüm yolları bul
find_paths(Start, End, Paths) :-
    findall(Path, find_path(Start, End, Path), Paths).

% Tek bir yol bulma
find_path(Start, End, Path) :-
    find_path(Start, End, [Start], Path).

find_path(Current, Current, _, [Current]).
find_path(Current, End, Visited, [Current | Path]) :-
    route(Current, Next, _),
    \+ member(Next, Visited),
    find_path(Next, End, [Next | Visited], Path).

% Bir yolun uzunluğunu ve süresini bulma
path_length_time([], 0, 0).
path_length_time([_], 0, 0).
path_length_time([Place1, Place2 | Rest], Length, Time) :-
    route(Place1, Place2, TravelTime),
    path_length_time([Place2 | Rest], RemainingLength, RemainingTime),
    Length is RemainingLength + 1,
    Time is RemainingTime + TravelTime.



% En kısa süren yolu bulma
find_shortest_path(Start, End, ShortestPath) :-
    find_paths(Start, End, Paths),
    find_shortest_path_helper(Paths, ShortestPath).

find_shortest_path_helper([Path], Path).
find_shortest_path_helper([Path1, Path2 | Rest], ShortestPath) :-
    path_length_time(Path1, _, Time1),
    path_length_time(Path2, _, Time2),
    Time1 =< Time2,
    find_shortest_path_helper([Path1 | Rest], ShortestPath).
find_shortest_path_helper([Path1, Path2 | Rest], ShortestPath) :-
    path_length_time(Path1, _, Time1),
    path_length_time(Path2, _, Time2),
    Time1 > Time2,
    find_shortest_path_helper([Path2 | Rest], ShortestPath).

% En kisa suren yolun toplam süresini bulma
shortest_path_total_time(Start, End, TotalTime) :-
    find_shortest_path(Start, End, ShortestPath),
    path_length_time(ShortestPath, _, TotalTime).

% Bir delivery_personin belirli bir delivery_objecti belirli bir teslimat noktasına götürmesi için geçen toplam süreyi hesapla
delivery_person_total_delivery_time(DeliveryPersonID, DeliveryObjectID, TotalTime) :-
    delivery_person(DeliveryPersonID, _, _, _, CurrentLocation),
    delivery_object(DeliveryObjectID, _, ObjectLocation, DeliveryPlace, _, _),
    find_shortest_path(CurrentLocation, ObjectLocation, DeliveryToObjectPath),
    find_shortest_path(ObjectLocation, DeliveryPlace, ObjectToDeliveryPlacePath),
    path_length_time(DeliveryToObjectPath, _, TravelTimeToDeliveryObject),
    path_length_time(ObjectToDeliveryPlacePath, _, TravelTimeToObjectDeliveryPlace),
    TotalTime is TravelTimeToDeliveryObject + TravelTimeToObjectDeliveryPlace.

% Kargonun taşınması gerekiyorsa ve taşıyan bir kişi yoksa
find_suitable_delivery_person(DeliveryObjectID, DeliveryPersonID, DeliveryPersonLocation, DeliveryTime) :-
    delivery_object(DeliveryObjectID, Weight, PickUpPlace, DropOffPlace, Urgency, InTransitPerson),
    InTransitPerson = none,
    delivery_person(DeliveryPersonID, Capacity, WorkHours, none, DeliveryPersonLocation),
    Capacity >= Weight, 
    delivery_person_total_delivery_time(DeliveryPersonID, DeliveryObjectID, TotalTime), 
    WorkHours >= TotalTime,
    DeliveryTime = TotalTime.

% Kargo taşınıyorsa, taşıyan kişinin konumunu ve taşıma suresini döndür
find_suitable_delivery_person(DeliveryObjectID, DeliveryPersonID, DeliveryPersonLocation, DeliveryTime) :-
    delivery_object(DeliveryObjectID, _,ObjectLocation, DeliveryPlace, _, InTransitPerson),
    InTransitPerson \= none, 
    delivery_person(InTransitPerson, _, _, _, DeliveryPersonLocation),
    find_shortest_path(DeliveryPersonLocation, DeliveryPlace, ShortestPath),
    path_length_time(ShortestPath, _, TotalTime),
    DeliveryPersonID = InTransitPerson,
    
    DeliveryTime = TotalTime. % Kargonun taşınma suresini döndür

% Örnek kullanım:
% find_suitable_delivery_person(5, DeliveryPersonID, DeliveryPersonLocation, DeliveryTime).
