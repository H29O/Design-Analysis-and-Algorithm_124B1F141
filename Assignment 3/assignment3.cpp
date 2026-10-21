#include &lt;iostream&gt;
#include &lt;vector&gt;
#include &lt;algorithm&gt;
#include &lt;iomanip&gt;

using namespace std;

struct Item {
string name;
double weight;
double value;
bool divisible;
int priority;

Item(string n, double w, double v, bool d, int p)
: name(n), weight(w), value(v), divisible(d), priority(p) {}

double valuePerWeight() const {
return value / weight;
}
};

// Sort by priority, then value/weight
bool compare(const Item&amp; a, const Item&amp; b) {
if (a.priority == b.priority)

return a.valuePerWeight() &gt; b.valuePerWeight();
return a.priority &lt; b.priority;
}

double fractionalKnapsack(vector&lt;Item&gt;&amp; items, double capacity, double&amp; totalWeightCarried) {
sort(items.begin(), items.end(), compare);

cout &lt;&lt; &quot;\nSorted Items (by Priority, then Value/Weight):\n&quot;;
cout &lt;&lt; left &lt;&lt; setw(20) &lt;&lt; &quot;Item&quot;
&lt;&lt; setw(10) &lt;&lt; &quot;Weight&quot;
&lt;&lt; setw(10) &lt;&lt; &quot;Value&quot;
&lt;&lt; setw(12) &lt;&lt; &quot;Priority&quot;
&lt;&lt; setw(15) &lt;&lt; &quot;Value/Weight&quot;
&lt;&lt; setw(15) &lt;&lt; &quot;Type&quot; &lt;&lt; &quot;\n&quot;;

for (const auto&amp; item : items) {
cout &lt;&lt; left &lt;&lt; setw(20) &lt;&lt; item.name
&lt;&lt; setw(10) &lt;&lt; item.weight
&lt;&lt; setw(10) &lt;&lt; item.value
&lt;&lt; setw(12) &lt;&lt; item.priority
&lt;&lt; setw(15) &lt;&lt; fixed &lt;&lt; setprecision(2) &lt;&lt; item.valuePerWeight()
&lt;&lt; setw(15) &lt;&lt; (item.divisible ? &quot;Divisible&quot; : &quot;Indivisible&quot;) &lt;&lt; &quot;\n&quot;;
}

double totalValue = 0.0;

totalWeightCarried = 0.0;

cout &lt;&lt; &quot;\nItems selected for transport:\n&quot;;

for (const auto&amp; item : items) {
if (capacity &lt;= 0) break;

if (item.divisible) {
double takenWeight = min(item.weight, capacity);
double takenValue = item.valuePerWeight() * takenWeight;
totalValue += takenValue;
capacity -= takenWeight;
totalWeightCarried += takenWeight;

cout &lt;&lt; &quot; - &quot; &lt;&lt; item.name &lt;&lt; &quot;: &quot; &lt;&lt; takenWeight &lt;&lt; &quot; kg, Utility = &quot; &lt;&lt; takenValue
&lt;&lt; &quot;, Priority = &quot; &lt;&lt; item.priority &lt;&lt; &quot;, Type = Divisible\n&quot;;
} else {
if (item.weight &lt;= capacity) {
totalValue += item.value;
capacity -= item.weight;
totalWeightCarried += item.weight;

cout &lt;&lt; &quot; - &quot; &lt;&lt; item.name &lt;&lt; &quot;: &quot; &lt;&lt; item.weight &lt;&lt; &quot; kg, Utility = &quot; &lt;&lt; item.value
&lt;&lt; &quot;, Priority = &quot; &lt;&lt; item.priority &lt;&lt; &quot;, Type = Indivisible\n&quot;;
}

}
}

return totalValue;
}

int main() {
int n;
cout &lt;&lt; &quot;Enter number of relief items: &quot;;
cin &gt;&gt; n;

vector&lt;Item&gt; items;
for (int i = 0; i &lt; n; ++i) {
string name;
double weight, value;
int divisibleInt, priority;

cout &lt;&lt; &quot;\nItem #&quot; &lt;&lt; (i + 1) &lt;&lt; &quot;:\n&quot;;
cout &lt;&lt; &quot;Name: &quot;;
cin.ignore(); // clear newline
getline(cin, name);
cout &lt;&lt; &quot;Weight (kg): &quot;;
cin &gt;&gt; weight;
cout &lt;&lt; &quot;Utility Value: &quot;;
cin &gt;&gt; value;

cout &lt;&lt; &quot;Is it divisible? (1 = Yes, 0 = No): &quot;;
cin &gt;&gt; divisibleInt;
cout &lt;&lt; &quot;Priority (1 = High, 2 = Medium, 3 = Low): &quot;;
cin &gt;&gt; priority;

items.emplace_back(name, weight, value, divisibleInt == 1, priority);
}

double capacity;
cout &lt;&lt; &quot;\nEnter maximum weight capacity of the boat (in kg): &quot;;
cin &gt;&gt; capacity;

double totalWeightCarried;
double maxValue = fractionalKnapsack(items, capacity, totalWeightCarried);

cout &lt;&lt; &quot;\n===== Final Report =====\n&quot;;
cout &lt;&lt; &quot;Total weight carried: &quot; &lt;&lt; fixed &lt;&lt; setprecision(2) &lt;&lt; totalWeightCarried &lt;&lt; &quot; kg\n&quot;;
cout &lt;&lt; &quot;Total utility value carried: &quot; &lt;&lt; fixed &lt;&lt; setprecision(2) &lt;&lt; maxValue &lt;&lt; &quot; units\n&quot;;

return 0;
}
