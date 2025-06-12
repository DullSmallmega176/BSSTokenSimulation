# --- simulation configuration ---
ELAPSETIME = 3600000 # ELAPSETIME - how many milliseconds to simulate
ENABLEGRAPH = False # --- WARNING --- this will hog memory. be careful.
LOGDATAINTERVAL = 100 # This will help reduce memory with graph mode, higher = less accurate.
'''
for graph display to work. you'll have to install this.
https://matplotlib.org/stable/install/index.html
'use the pip install command on console/terminal.
'''
# --- bee stats ---
BEE = 'basic'
GIFTED = True  # GIFTED - controls if it should take into concideration about inspire
# --- mutations ---
BMS = 0     # BMS - Bee Movespeed - affects the bee's movement
BAR = 0     # BAR - Bee Ability Rate - affects the bee's TGC and TAC
# --- player/bee booster stats --- for better accuracy so we don't have to spend quads on testing.
PBAR = 131  # PBAR - Player Bee Ability Rate - your BAR in the system page
PERCBMS = 11  # PERCBMS - Percentage BMS - your total BMS percentage boost. you can do math to find it out.
ADDBMS = 0 # ADDBMS - Add BMS - Adding to base movespeed of a bee.
BEELVL = 21 # BEELVL - Bee Level - this increases BMS by 3% per level
# --- extra stats --- this is for beequips and stuff
BBAR = 0  # BBAR - Beequip BAR - extra buffs given from other beequips, no hive bonus
BTOKEN = [] # BTOKEN - Beequip Token - extra token spawn from beequips
'''
BaseMovespeed*(1+((level-1)*0.03))*x = ActualBeeSpeed
Ex:
base movespeed - 14
level - 5
actual movespeed = 15.99
x = 1.019770408163 -> round to the nearest 2nd decimal.
x = 1.02 -> my total percentage is 2%
'''
BEES = {'basic':{'speed':14,'gather':4,'token':[], 'gifted':['inspire']},'bomber':{'speed':15.4,'gather':4,'token':['bomb'], 'gifted':['inspire']},'brave':{'speed':16.8,'gather':4,'token':[], 'gifted':['inspire']},'bumble':{'speed':10.5,'gather':4,'token':['bomb'], 'gifted':['inspire']},'cool':{'speed':14,'gather':3,'token':['boost'], 'gifted':['inspire']},'hasty':{'speed':19.6,'gather':3,'token':['haste'], 'gifted':['inspire']},'looker':{'speed':14,'gather':4,'token':['focus'], 'gifted':['inspire']},'rad':{'speed':14,'gather':4,'token':['boost'], 'gifted':['inspire']},'rascal':{'speed':16.1,'gather':4,'token':['bomb'], 'gifted':['inspire']},'stubborn':{'speed':11.9,'gather':4,'token':['mark'], 'gifted':['inspire']},'bubble':{'speed':16.1,'gather':4,'token':['bomb'], 'gifted':['inspire']},'bucko':{'speed':15.4,'gather':4,'token':['boost'], 'gifted':['inspire']},'commander':{'speed':14,'gather':4,'token':['focus', 'bomb'], 'gifted':['inspire']},'demo':{'speed':16.8,'gather':4,'token':['bomb'], 'gifted':['inspire']},'exhausted':{'speed':10.5,'gather':4.6,'token':['bomb', 'tokenLink'], 'gifted':['inspire']},'fire':{'speed':11.2,'gather':4,'token':['bomb'], 'gifted':['inspire']},'frosty':{'speed':11.2,'gather':4,'token':['boost', 'bomb'], 'gifted':['inspire']},'honey':{'speed':14,'gather':4,'token':['honeyGift'], 'gifted':['inspire']},'rage':{'speed':15.4,'gather':4,'token':['tokenLink'], 'gifted':['inspire']},'riley':{'speed':15.4,'gather':2,'token':['boost'], 'gifted':['inspire']},'shocked':{'speed':19.6,'gather':4,'token':['haste', 'tokenLink'], 'gifted':['inspire']},'baby':{'speed':10.5,'gather':5,'token':['babyLove'], 'gifted':['inspire']},'carpenter':{'speed':11.2,'gather':3,'token':['mark', 'mark'], 'gifted':['inspire']},'demon':{'speed':10.5,'gather':4,'token':['bomb', 'bomb'], 'gifted':['inspire']},'diamond':{'speed':14,'gather':4,'token':['boost', 'honeyGift'], 'gifted':['inspire']},'lion':{'speed':19.6,'gather':4,'token':['bomb'], 'gifted':['inspire']},'music':{'speed':16.1,'gather':4,'token':['melody', 'focus', 'tokenLink'], 'gifted':['inspire']},'ninja':{'speed':21,'gather':2,'token':['haste', 'bomb'], 'gifted':['inspire']},'shy':{'speed':18.2,'gather':2,'token':['boost', 'bomb'], 'gifted':['inspire']},'buoyant':{'speed':14,'gather':5,'token':['bomb','inflateBalloon'], 'gifted':['inspire', 'surpriseParty']},'fuzzy':{'speed':11.9,'gather':6,'token':['fuzzBombs', 'bomb'], 'gifted':['inspire', 'pollenHaze']},'precise':{'speed':11.2,'gather':4,'token':['targetPractice'], 'gifted':['inspire']},'spicy':{'speed':14,'gather':4,'token':['inferno', 'rage'], 'gifted':['inspire', 'flameFuel']},'tadpole':{'speed':11.2,'gather':6,'token':['boost', 'summonFrog'], 'gifted':['inspire', 'babyLove']},'vector':{'speed':16.24,'gather':4,'token':['mark', 'triangulate'], 'gifted':['inspire', 'markSurge']},'bear':{'speed':14,'gather':2,'token':['bearMorph'], 'gifted':['inspire']},'cobalt':{'speed':18.2,'gather':4,'token':['pulse', 'bombSync'], 'gifted':['inspire']},'crimson':{'speed':18.2,'gather':4,'token':['pulse', 'bombSync'], 'gifted':['inspire']},'digital':{'speed':11.9,'gather':4,'token':['glitch', 'mindHack'], 'gifted':['inspire', 'mapCorruption']},'festive':{'speed':16.1,'gather':4,'token':['festiveGift', 'mark', 'bomb'], 'gifted':['inspire']},'gummy':{'speed':14,'gather':4,'token':['gumdropBarrage', 'glob'], 'gifted':['inspire']},'photon':{'speed':21,'gather':2,'token':['beamstorm', 'haste'], 'gifted':['inspire']},'puppy':{'speed':16.1,'gather':4,'token':['fetch', 'puppyLove'], 'gifted':['inspire']},'tabby':{'speed':16.1,'gather':4,'token':['scratch', 'tabbyLove'], 'gifted':['inspire']},'vicious':{'speed':17.5,'gather':4,'token':['impale', 'bomb'], 'gifted':['inspire']},'windy':{'speed':19.6,'gather':3,'token':['boost', 'rainCloud', 'tornado'], 'gifted':['inspire']}}
TOKENLIST = {'haste':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},'focus':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},'rage':{'TGC':50, 'TAC':15, 'TSR':1},'tokenLink':{'TGC':5, 'TAC':5, 'TSR':1/3},'mark':{'TGC':20, 'TAC':5, 'TSR':1/4},'babyLove':{'TGC':60, 'TAC':5, 'TSR':1/9},'melody':{'TGC':45, 'TAC':15, 'TSR':1/3},'bomb':{'TGC':8, 'TAC':4, 'TSR':1/4},'boost':{'TGC':4.5, 'TAC':4.5, 'TSR':1/3},'honeyGift':{'TGC':120, 'TAC':60, 'TSR':1/4},'triangulate':{'TGC':20, 'TAC':10, 'TSR':1/3},'markSurge':{'TGC':24, 'TAC':6, 'TSR':1/4},'inferno':{'TGC':30, 'TAC':5, 'TSR':1/6},'flameFuel':{'TGC':45, 'TAC':15, 'TSR':1/3},'summonFrog':{'TGC':50, 'TAC':10, 'TSR':1/4},'inflateBalloon':{'TGC':28, 'TAC':8, 'TSR':1/4},'surpriseParty':{'TGC':360, 'TAC':15, 'TSR':1/8},'targetPractice':{'TGC':24, 'TAC':6, 'TSR':1/4},'fuzzBombs':{'TGC':20, 'TAC':10, 'TSR':1/3},'pollenHaze':{'TGC':75, 'TAC':15, 'TSR':1/6},'beamstorm':{'TGC':20, 'TAC':10, 'TSR':1/3},'scratch':{'TGC':12, 'TAC':6, 'TSR':1/4},'tabbyLove':{'TGC':120, 'TAC':60, 'TSR':1/5},'fetch':{'TGC':140, 'TAC':5, 'TSR':1/2},'puppyLove':{'TGC':80, 'TAC':10, 'TSR':1/5},'bearMorph':{'TGC':45, 'TAC':15, 'TSR':1/2},'pulse':{'TGC':12, 'TAC':6, 'TSR':1/4},'bombSync':{'TGC':30, 'TAC':15, 'TSR':1/3},'festiveGift':{'TGC':480, 'TAC':30, 'TSR':1/8},'glob':{'TGC':6, 'TAC':3, 'TSR':1/3},'gumdropBarrage':{'TGC':9, 'TAC':4, 'TSR':1/4},'impale':{'TGC':30, 'TAC':1, 'TSR':1},'rainCloud':{'TGC':45, 'TAC':20, 'TSR':1/2},'tornado':{'TGC':80, 'TAC':10, 'TSR':1/3},'glitch':{'TGC':60, 'TAC':10, 'TSR':1/3},'mapCorruption':{'TGC':360, 'TAC':15, 'TSR':1/8},'mindHack':{'TGC':90, 'TAC':2, 'TSR':1/3},'smile':{'TGC':0, 'TAC':15, 'TSR':1},'festiveMark':{'TGC':300, 'TAC':30, 'TSR':1/6},'snowglobeShake':{'TGC':300, 'TAC':30, 'TSR':1/6},'inspire':{'TGC':60, 'TAC':5, 'TSR':1/100},}
import random, os
from timeit import default_timer as timer
try:
    import matplotlib.pyplot as plt
except ImportError:
    ENABLEGRAPH = False
    plt = None
class BeeSimulate:
    def __init__(self, beeName):
        self.beeName = beeName
        if beeName not in BEES:
            raise ValueError("invalid bee")
        self.bee = BEES[beeName]
        self.speed = self.adjSpeed(self.bee['speed'], BMS+ADDBMS, PERCBMS, BEELVL)
        self.gatherTime = self.bee['gather']*1000
        self.tlist = self.bee['token'] + (self.bee['gifted'] if GIFTED else []) + BTOKEN
        self.tokens = {}
        self.timers = {}
        for i in range(len(self.tlist)):
            tokenTGC = round(self.adjCooldwn(TOKENLIST[self.tlist[i]]['TGC'], PBAR, BAR, BBAR)*1000)
            tokenTAC = round(self.adjCooldwn(TOKENLIST[self.tlist[i]]['TAC'], PBAR, BAR, BBAR)*1000)
            tokenTSR = self.adjChance(TOKENLIST[self.tlist[i]]['TSR'], PBAR, BAR, BBAR)
            self.tokens[i] = {'name':self.tlist[i],'TGC':tokenTGC,'TAC':tokenTAC,'TSR':tokenTSR}
            self.timers[i] = {'name':self.tlist[i],'TGC':tokenTGC,'TAC':tokenTAC,'total':0}
        self.timers['gather'] = 0
        self.timers['movement'] = self.movementEffect(self.speed)
        self.currentTime = 0
        self.totalTokens = 0
        self.timeSeries = []
        self.movementSeries = []
        self.gatherSeries = []
        self.tokenActivation = {token: [] for token in range(len(self.tlist))}
        self.frogActive = False
        self.frogDuration = 0
        self.frogTokenIndex = next((i for i, t in enumerate(self.tlist) if t == 'summonFrog'), None)
        self.frogCount = 0
    def adjCooldwn(self, base, pbar, bar, bbar):
        return base/(((pbar+bbar)/100)*(1+(bar/100)))
    def adjSpeed(self, base, addbms, percbms, level):
        return (base+addbms)*(1+(percbms/100))*(1+((level-1)*0.03))
    def adjChance(self, base, pbar, bar, bbar):
        return base*(1+(((pbar-100)+bar+bbar)*0.01))
    def spinEffect(self, tsr):
        if random.random() <= tsr:
            return 2
        return 0
    def movementEffect(self, walkspeed):
        studs = random.randint(1, 20)*4
        return round((studs/walkspeed)*1000)
    def reduceCooldown(self):
        for token in self.timers:
            if token not in ['gather', 'movement']:
                if self.timers[token]['TGC'] > 0:
                    self.timers[token]['TGC'] -= 1
                if self.timers[token]['TAC'] > 0:
                    self.timers[token]['TAC'] -= 1
        if self.timers['movement'] > 0:
            self.timers['movement'] -= 1
        elif not self.timers['gather']:
            self.timers['movement'] = self.movementEffect(self.speed)
    def tokenAttempt(self):
        if self.timers['gather'] == 0 and self.timers['movement'] == 0:
            for token in self.timers:
                if token in ['gather', 'movement']:
                    continue
                tokenData = self.tokens[token]
                if self.timers[token]['TGC'] == 0 and self.timers[token]['TAC'] == 0 and random.random() < tokenData['TSR']:
                    self.timers[token]['TGC'] = tokenData['TGC']
                    self.timers[token]['TAC'] = tokenData['TAC']
                    self.timers[token]['total'] += 1
                    self.totalTokens += 1
                    self.timers['gather'] = self.gatherTime + 1000
                    if self.tlist[token] == 'summonFrog' and not self.frogActive:
                        self.frogActive = True
                        self.frogDuration = 20000 + (BEELVL-1)*2000
                    return
            self.timers['gather'] = self.gatherTime
    def updateGather(self):
        if self.timers['gather']:
            self.timers['gather'] -= 1
    def step(self):
        minSkip = min([self.timers['movement'], self.timers['gather']]+[self.timers[token]['TGC'] for token in self.timers if token not in ['gather', 'movement']]+[self.timers[token]['TAC'] for token in self.timers if token not in ['gather', 'movement']])
        if minSkip > 1:
            self.currentTime += minSkip
            for token in self.timers:
                if token in ['gather', 'movement']:
                    self.timers[token] = max(0, self.timers[token]-minSkip)
                else:
                    self.timers[token]['TGC'] = max(0, self.timers[token]['TGC']-minSkip)
                    self.timers[token]['TAC'] = max(0, self.timers[token]['TAC']-minSkip)
        else:
            self.reduceCooldown()
            if self.timers['gather'] == 0 and self.timers['movement'] == 0:
                self.tokenAttempt()
            self.updateGather()
            self.currentTime += 1
        if ENABLEGRAPH and self.currentTime % LOGDATAINTERVAL == 0:
            self.timeSeries.append(self.currentTime)
            self.movementSeries.append(self.timers['movement'])
            self.gatherSeries.append(self.timers['gather'])
            for token in range(len(self.tlist)):
                self.tokenActivation[token].append(self.timers[token]['TGC'])
        if self.frogActive:
            self.frogDuration -= minSkip if minSkip > 1 else 1
            if self.frogDuration <= 0:
                self.frogActive = False
                self.frogCount += 1
    def plotGraph(self):
        if not ENABLEGRAPH or plt is None:
            return
        plt.figure(figsize=(12,6))
        plt.subplot(2,1,1)
        plt.plot(self.timeSeries, self.movementSeries, label="movement cooldown", color='blue')
        plt.plot(self.timeSeries, self.gatherSeries, label="gather cooldown", color='green')
        plt.xlabel("time - ms")
        plt.ylabel("cooldowm time")
        plt.title("bee/token simulation")
        plt.legend()
        plt.subplot(2,1,1)
        for token in range(len(self.tlist)):
            plt.plot(self.timeSeries, self.tokenActivation[token], label=f"token: {self.tlist[token]}")
        plt.xlabel("time - ms")
        plt.ylabel("cooldown time")
        plt.title("token cooldown over time")
        plt.legend()
        plt.tight_layout()
        plt.show()
    def run(self):
        start = timer()
        while self.currentTime < ELAPSETIME:
            self.step()
        end = timer()-start
        minutes = ELAPSETIME/60000
        tokenAverage = self.totalTokens/minutes
        print(f'it took {end:.2f} seconds to simulate {minutes} minutes')
        print("-- bee stats --")
        print(f"{self.beeName} | mutations - Movespeed: {BMS}, Ability Rate: {BAR}")
        print(f"{'Token':<20} {'TGC (s)':>10} {'TAC (s)':>10} {'TSR (%)':>10}")
        print("-" * 50)

        for i, token in self.tokens.items():
            name = token['name']
            tgc_s = token['TGC'] / 1000
            tac_s = token['TAC'] / 1000
            tsr_percent = token['TSR'] * 100
            print(f"{name:<20} {tgc_s:>10.2f} {tac_s:>10.2f} {tsr_percent:>10.2f}")
        print("-" * 50)
        print(f"total tokens produced: {self.totalTokens} ({tokenAverage:.2f} per minute)")
        print("-- each token breakdown --")
        for token in self.timers:
            if token not in ['gather', 'movement']:
                seconds = 60 / (self.timers[token]['total']/minutes) if self.timers[token]['total'] else 0
                print(f"-  {self.timers[token]['name']}: {self.timers[token]['total']} - Avg: {(self.timers[token]['total']/minutes):.2f} per min. ({seconds:.2f} seconds)")
        if self.frogTokenIndex is not None:
            minutes = ELAPSETIME/60000
            frogAvg = self.frogCount/minutes
            frogSeconds = 60/frogAvg if frogAvg else 0
            print(f"- frogs: {self.frogCount} - Avg: {frogAvg:.2f} per min. ({frogSeconds:.2f} seconds)")
        self.plotGraph()
if __name__ == "__main__":
    os.system('cls')
    print("script is running")
    simulation = BeeSimulate(BEE)
    simulation.run()
