grade = input("Enter Grade(A/B) : ");
if(grade == "A" or grade == "a"):
	basic = 10000
	allow = 1700
else:
	basic = 4567
	allow = 1500
HRA = basic/5
DA = basic/2
PF = 0.11*basic

print("Gross salary = {}".format(basic+HRA+DA+allow-PF))
