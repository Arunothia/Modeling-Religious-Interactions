f = open("data.txt",'w')

a = 3
b = 6
c = 1
d = 5
ep1 = 7
ep2 = 7
qc1 = 0.3
qc2 = 0.4
qd1 = 0.8
qd2 = 0.6
b1 = 0.3
b2 = 0.3

action1 = 'x'
action2 = 'y'

payoffs = {}
payoffs["cc"] = [d+ep1*(1-2*qc1),d+ep2*(1-2*qc2)]
payoffs["cd"] = [c+ep1*(1-2*qc1),b+ep2*(1-2*qd2)]
payoffs["dc"] = [b+ep1*(1-2*qd1),c+ep2*(1-2*qc2)]
payoffs["dd"] = [a+ep1*(1-2*qd1),a+ep2*(1-2*qd2)]

def play():
    global b1,b2,action1,action2
    c_payoff1 = b1*payoffs["cc"][0] + (1-b1)*payoffs["cd"][0]
    d_payoff1 = b1*payoffs["dc"][0] + (1-b1)*payoffs["dd"][0]
    if(c_payoff1 >= d_payoff1):
        action1 = 'c'
    else:
        action1 = 'd'
    c_payoff2 = b2*payoffs["cc"][1] + (1-b2)*payoffs["dc"][1]
    d_payoff2 = b2*payoffs["cd"][1] + (1-b2)*payoffs["dd"][1]
    if(c_payoff2 >= d_payoff2):
        action2 = 'c'
    else:
        action2 = 'd'
    if(action2 == 'c'):
        b1 = min(b1 + al,1)
    else:
        b1 = max(b1 - al,0)
    if(action1 == 'c'):
        b2 = min(b2 + al,1)
    else:
        b2 = max(b2 - al,0)
    #f.write(str(c_payoff1) + " " + str(d_payoff1) + " " + action1 + " " + action2 + "\n")

values = {}
values["cc"] = 1
values["cd"] = 2
values["dc"] = 3
values["dd"] = 4
def main():
    global al
    al = 0
    print payoffs
    global b1,b2,qc1,qc2,qd1,qd2,action1,action2
    cont_list = []
    i = 0
    while(i<=1):
        cont_list.append(i)
        i += 0.1
    cont_list2 = [0.02]
    for al in cont_list2:
        f = open("d" + str(al*10) + ".csv",'w')
        for qc1 in cont_list:
            for qc2 in cont_list:
                for qd1 in cont_list:
                    for qd2 in cont_list:
                        b1 = 0.4
                        b2 = 0.3
                        payoffs["cc"] = [d+ep1*(1-2*qc1),d+ep2*(1-2*qc2)]
                        payoffs["cd"] = [c+ep1*(1-2*qc1),b+ep2*(1-2*qd2)]
                        payoffs["dc"] = [b+ep1*(1-2*qd1),c+ep2*(1-2*qc2)]
                        payoffs["dd"] = [a+ep1*(1-2*qd1),a+ep2*(1-2*qd2)]
                        #f.write(str(al) + "\n")
                        for i in range(100):
                            play()
                        f.write(str(qc1-qd1) +", " + str(qc2-qd2) + ", " + str(values[action1+action2]) + "\n")
                        print "on it\n"
main()
