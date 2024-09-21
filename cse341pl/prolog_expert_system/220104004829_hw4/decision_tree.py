from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, export_text
from sklearn import tree
import matplotlib.pyplot as plt

# Iris dataset yükleme
iris = load_iris()
X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, test_size=0.2, random_state=42)

# Decision Tree oluşturma
clf = DecisionTreeClassifier()
clf.fit(X_train, y_train)

# Karar ağacını görselleştirme ve PNG olarak kaydetme
fig, ax = plt.subplots(figsize=(12,12))
tree.plot_tree(clf, filled=True, feature_names=iris.feature_names, class_names=iris.target_names, rounded=True, ax=ax)
plt.savefig('decision_tree.png')