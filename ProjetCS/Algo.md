<h3>1.Initialisation</h3>
<ul>
<li> &Pi  est calculé par une heuristique maison</li>
<li> Z est calculé par l'heuristique glouton</li>
<li> On fixe L, U, et t = 1</li>
</ul>

<h3>2.Calcul du nouveau &Pi (Methode des volumes)</h3>

<h3>3. Phase de calcul</h3>
<ul>
<li>Calcul Z = argmin{(c - &Pi*A)} (c=1)
<ul>
<li>On calcul L^k(&Pi) avec KP (voir Vanderbeck page 11)</li>
<li>On calcul L(&Pi) avec le L^k(&Pi) obtenu</li>
</ul>
</li>
<li>Calcul du sous-gradiant g = (a - A*Z)  (a=1)</li>
<li>Calcul de LB = &Pi*a + Z*g</li>
</ul>

<h3>MAJ de la solution Dual</h3>
<ul>
<li>Si LB_chapo >= LB  alors</li>
<ul><li>&Pi_chapo = &Pi</li><li>LB_chapo = LB</li>
</ul>

<h3>Calcul de la solution Primal</h3>
<h3>MAJ de la solution primal courante</h3>
<h3>Ajout de Z au bundle </h3>
<h3>retour à 2 tant qu'on remplit pas nos conditions</h3>
