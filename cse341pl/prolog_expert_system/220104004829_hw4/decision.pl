classify(SepalLength, SepalWidth, PetalLength, PetalWidth, Type) :-
    (PetalLength > 2.45 ->
        (PetalLength > 4.75 ->
            (PetalWidth > 1.75 ->
                (PetalLength > 4.85 ->
                    Type = 'Iris-Virginica'
                    ;
                    (SepalLength > 5.95 ->
                        Type = 'Iris-Versicolor'
                        ;
                        Type = 'Iris-Virginica'
                    )
                )
                ;
                (PetalLength > 4.95 ->
                    (PetalWidth > 1.55 ->
                        (SepalLength > 6.95 ->
                            Type = 'Iris-Virginica'
                            ;
                            Type = 'Iris-Versicolor'
                        )
                        ;
                        Type = 'Iris-Virginica'
                    )
                    ;
                    Type = 'Iris-Versicolor'
                )
            )
            ;
            (PetalWidth > 1.65 ->
                Type = 'Iris-Virginica'
                ;
                Type = 'Iris-Versicolor'
            )
        )
        ;
        Type = 'Iris-Setosa'
    ).
