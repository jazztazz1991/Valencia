import time

def make_decision(current_time, has_to_work, is_tired, free_time_hours):
		   
		    current_hour = int(time.strptime(current_time, "%I:%M %p").tm_hour)
		    
		    decisions = {
		        "watch_show": "Ronny watches a show.",
		        "play_games": "Ronny plays video games.",
		        "both": "Ronny plays video games and watches a show."
		    }

		    if current_hour >= 23 and has_to_work:
		        return decisions["watch_show"]
		    else:
		        if is_tired:
		            return decisions["watch_show"]
		        else:
		            if free_time_hours >= 2:
		                return decisions["both"]
		            else:
		                return decisions["play_games"]
	

print(make_decision("11:30 PM", has_to_work=True, is_tired=False, free_time_hours=3))
print("-" * 20)

print(make_decision("9:00 PM", has_to_work=True, is_tired=True, free_time_hours=3))
print("-" * 20)

print(make_decision("10:00 PM", has_to_work=False, is_tired=False, free_time_hours=2))
print("-" * 20)

print(make_decision("10:30 PM", has_to_work=True, is_tired=False, free_time_hours=1))
print("-" * 20)