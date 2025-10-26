<?php
/*
    Author: Cody Chase
    Date: 9/12/2025
    Alternate Scripting Language Scenario
*/


// Decision-making function based on time, work status, tiredness, and free time.
function make_decision($current_time, $has_to_work, $is_tired, $free_time_hours) {
    // Convert 12-hour time to 24-hour format and get the hour.
    $current_hour = (int)date("G", strtotime($current_time));

    $decisions = [
        "watch_show" => "Ronny watches a show.",
        "play_games" => "Ronny plays video games.",
        "both" => "Ronny plays video games and watches a show."
    ];

    if ($current_hour >= 23 && $has_to_work) {
        return $decisions["watch_show"];
    } else {
        if ($is_tired) {
            return $decisions["watch_show"];
        } else {
            if ($free_time_hours >= 2) {
                return $decisions["both"];
            } else {
                return $decisions["play_games"];
            }
        }
    }
}

echo make_decision("11:30 PM", true, false, 3) . "\n";
echo str_repeat("-", 20) . "\n";

echo make_decision("9:00 PM", true, true, 3) . "\n";
echo str_repeat("-", 20) . "\n";

echo make_decision("10:00 PM", false, false, 2) . "\n";
echo str_repeat("-", 20) . "\n";

echo make_decision("10:30 PM", true, false, 1) . "\n";
echo str_repeat("-", 20) . "\n";

?>